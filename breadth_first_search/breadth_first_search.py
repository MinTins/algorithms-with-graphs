import networkx as nx
import matplotlib.pyplot as plt

# зчитуємо граф з файлу
with open('graph.txt', 'r') as f:
    n,m,start_node = map(int, f.readline().split())
    data = [list( line.strip().split() ) for line in f.readlines()]


# створюємо граф
G = nx.Graph()

# додаємо вершини до графа
for i in range(n):
    G.add_node(i)

# додаємо ребра до графа
for i in range(len(data)):
    u = int(data[i][0])
    v = int(data[i][1])
    G.add_edge(u, v)

# візуалізуємо граф
pos = nx.spring_layout(G)

nx.draw_networkx_nodes(G, pos, node_color='lightblue')
nx.draw_networkx_nodes(G, pos, nodelist=[start_node], node_color='blue')
nx.draw_networkx_edges(G, pos, edgelist=[(x,y) for x,y in G.edges() if x!=y], edge_color='black', width=1)    
nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
plt.axis('off')
#nx.draw(G, pos, with_labels=True)

# зберігаємо початковий стан графа
plt.savefig('temp0.png')


# створюємо чергу для зберігання вершин, які потрібно відвідати
queue = [start_node]

# створюємо список відвіданих вершин
visited = [False] * n
visited[start_node] = True

# починаємо обхід графа
step = 1
while queue:
    # відвідуємо вершину з початку черги
    node = queue.pop(0)
    
    # знаходимо всі сусідні вершини
    neighbors = list(G.neighbors(node))
    
    # відмічаємо всі сусідні вершини, які ще не були відвідані
    for neighbor in neighbors:
        if not visited[neighbor]:
            visited[neighbor] = True
            queue.append(neighbor)
            
            # виділяємо ребро, яке веде до сусідньої вершини
            edge = (node, neighbor)
            nx.draw_networkx_edges(G, pos, edgelist=[edge], edge_color='r', width=3)
            
            # зберігаємо стан графа
            plt.savefig(f'temp{step}.png')
            step += 1

# зберігаємо кінцевий стан графа
plt.savefig(f'temp{step}.png')

# об'єднуємо всі зображення у гіфку
import imageio.v2 as imageio

images = []
for i in range(step+1):
    filename = f'temp{i}.png'
    images.append(imageio.imread(filename))

duration = 5 / len(images)  
imageio.mimsave('result.gif', images, duration=duration)


import os

for i in range(step+1):
    filename = f'temp{i}.png'
    os.remove(filename)