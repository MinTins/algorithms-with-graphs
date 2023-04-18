import networkx as nx
import matplotlib.pyplot as plt

# зчитуємо граф з файлу
with open('graph.txt', 'r') as f:
    n, m, s, e = map(int, f.readline().split())
    edges = []
    for i in range(m):
        u, v, w = map(int, f.readline().split())
        edges.append((u, v, w))

# створюємо граф
G = nx.Graph()
G.add_weighted_edges_from(edges)

# зберігаємо початковий стан графу
plt.figure(figsize=(8, 6))
pos = nx.spring_layout(G)
nx.draw_networkx(G, pos)
nx.draw_networkx_edge_labels(G, pos, edge_labels={(u, v): d['weight'] for u, v, d in G.edges(data=True)})
plt.savefig('temp0.png')

# алгоритм Форда-Фалкерсона
def ford_fulkerson(G, source, sink):
    # створюємо копію графу
    flow_graph = G.copy()
    # ініціалізуємо потік нулями
    for u, v, d in flow_graph.edges(data=True):
        d['flow'] = 0
    # шукаємо шляхи з source до sink
    while True:
        path = nx.shortest_path(flow_graph, source, sink, weight='weight')
        print(path)
        # якщо шляху немає, то вихід з циклу
        if not path or not path[1:]:
            break
        # знаходимо мінімальну пропускну здатність на шляху
        min_capacity = min(flow_graph[u][v]['weight'] for u, v in zip(path, path[1:]))
        # збільшуємо потік на шляху
        for u, v in zip(path, path[1:]):
            flow_graph[u][v]['flow'] += min_capacity
            flow_graph[v][u]['flow'] -= min_capacity
        break
    # обчислюємо максимальний потік
    max_flow = sum(flow_graph[source][v]['flow'] for v in flow_graph.neighbors(source))
    # повертаємо граф з потоками та максимальний потік
    return flow_graph, max_flow

# запускаємо алгоритм та зберігаємо кожен крок
step = 1
for u, v, d in G.edges(data=True):
    # виділяємо ребро
    flow_graph = G.copy()
    flow_graph[u][v]['color'] = 'red'
    # запускаємо алгоритм Форда-Фалкерсона
    flow_graph, max_flow = ford_fulkerson(flow_graph, s, v)
    # зберігаємо стан графу
    plt.figure(figsize=(8, 6))
    pos = nx.spring_layout(flow_graph)
    # малюємо ребра з різними кольорами
    edge_colors = ['red' if (u, v) == (u_, v_) else d.get('color', 'black') for u_, v_, d_ in flow_graph.edges(data=True)]
    nx.draw_networkx(flow_graph, pos, node_color='lightblue', node_size=500, edge_color=edge_colors, width=2)
    nx.draw_networkx_edge_labels(flow_graph, pos, edge_labels={(u_, v_): f"{d_['flow']}/{d_['weight']}" for u_, v_, d_ in flow_graph.edges(data=True)})
    plt.title(f"Max flow: {max_flow}")
    plt.savefig(f'temp{step}.png')
    step += 1

# зберігаємо кінцевий стан графу
plt.figure(figsize=(8, 6))
pos = nx.spring_layout(flow_graph)
nx.draw_networkx(flow_graph, pos, node_color='lightblue', node_size=500, edge_color=edge_colors, width=2)
nx.draw_networkx_edge_labels(flow_graph, pos, edge_labels={(u_, v_): f"{d_['flow']}/{d_['weight']}" for u_, v_, d_ in flow_graph.edges(data=True)})
plt.title(f"Max flow: {max_flow}")
plt.savefig(f'temp{step}.png')

# об'єднуємо всі зображення у гіфку
import imageio.v2 as imageio

images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 5 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)

# видаляємо тимчасові файли
import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)