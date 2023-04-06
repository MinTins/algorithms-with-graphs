import heapq
import networkx as nx
import matplotlib.pyplot as plt

# зчитуємо граф з файлу
with open('graph.txt', 'r') as f:
    n, m, s = map(int, f.readline().split())
    edges = [list(int(x) for  x in line.strip().split() ) for line in f.readlines()]

# створюємо граф
G = nx.Graph()
G.add_weighted_edges_from(edges)

# налаштування побудови
pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, node_color='lightblue')
nx.draw_networkx_nodes(G, pos, nodelist=[s], node_color='blue')
nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
plt.axis('off')

# побудова початкового графа
real_edges = [(x,y) for x,y,w in edges if x!=y and w>0]

nx.draw_networkx_edges(G, pos, edgelist=real_edges, edge_color='black', width=1)    
edge_labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, {k:x for k,x in edge_labels.items() if k in real_edges})
plt.savefig(f'temp0.png')


def dist(u, v):
    try:
        return G[u][v]['weight']
    except:
        return 0

def heuristic(u, v):
    return dist(u, v)

# функція для візуалізації кроків алгоритму
def visualize_path(path, step, finish=False):
    plt.title(f'Step {step}')

    nx.draw_networkx_nodes(G, pos, node_color='lightblue')
    plt.axis('off')

    # побудова початкового графа
    real_edges = [(x,y) for x,y,w in edges if x!=y and w>0]
    nx.draw_networkx_nodes(G, pos, nodelist=[x for y in path for x in y], node_color='r' if not finish else "g")
    nx.draw_networkx_edges(G, pos, edgelist=real_edges, edge_color='black', width=1)    
    nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
    edge_labels = nx.get_edge_attributes(G, "weight")
    nx.draw_networkx_edge_labels(G, pos, {k:x for k,x in edge_labels.items() if k in real_edges})
    nx.draw_networkx_edges(G, pos, edgelist=path, edge_color='red' if not finish else "green", width=2 if not finish else 3)
    plt.savefig(f'temp{step}.png')
    plt.close()
    

# алгоритм А*

step = 1
def A_star(start, end):
    global step
    # ініціалізація
    heap = [(0, start)]
    visited = set()
    parent = {start: None}
    g_score = {start: 0}
    f_score = {start: heuristic(start, end)}

    # основний цикл
    while heap:
        # вибираємо вершину з найменшою оцінкою f
        _, current = heapq.heappop(heap)
        visited.add(current)

        # якщо досягли кінцевої вершини, повертаємо шлях
        if current == end:
            path = []
            while current is not None:
                path.append(current)
                current = parent[current]
            path.reverse()
            visualize_path(list(zip(path, path[1:])), step)
            step+=1
            return path

        # розглядаємо всі сусідні вершини
        for neighbor in G.neighbors(current):
            if neighbor in visited:
                continue

            # розраховуємо нову відстань до сусідньої вершини
            tentative_g_score = g_score[current] + dist(current, neighbor)

            # якщо такої вершини ще немає в кучі, додаємо її
            if neighbor not in [x[1] for x in heap]:
                heapq.heappush(heap, (tentative_g_score + heuristic(neighbor, end), neighbor))
            # якщо нова відстань менша за попередню, оновлюємо значення
            elif tentative_g_score >= g_score[neighbor]:
                continue

            # оновлюємо значення відстані та оцінки f
            parent[neighbor] = current
            g_score[neighbor] = tentative_g_score
            f_score[neighbor] = tentative_g_score + heuristic(neighbor, end)

        # візуалізація поточного стану
        path = []
        for node in visited:
            if parent[node] is not None:
                path.append((parent[node], node))
        visualize_path(path, step)
        step += 1

    # якщо кінцева вершина недосяжна, повертаємо None
    return None




# запускаємо алгоритм та зберігаємо результат у гіфку
path = A_star(s, n-1)
visualize_path(list(zip(path, path[1:])), step, True)

import imageio.v2 as imageio
images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 10 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)


import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)