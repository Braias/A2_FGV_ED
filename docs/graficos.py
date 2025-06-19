import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

data_rbt = pd.read_csv("rbt_stats.csv")
data_bst = pd.read_csv("bst_stats.csv")
data_avl = pd.read_csv("avl_stats.csv")

def make_lineplot(x, y, title, scale=None, color_bst="blue", color_avl="green", color_rbt='#e60073'):
    fig, ax = plt.subplots(figsize=(5, 4))
    sns.lineplot(x=data_bst[x], y=data_bst[y], label="BST", color=color_bst, marker="o", ax=ax)
    sns.lineplot(x=data_avl[x], y=data_avl[y], label="AVL", color=color_avl, marker="o", ax=ax)
    sns.lineplot(x=data_rbt[x], y=data_rbt[y], label="RBT", color=color_rbt, marker="o", ax=ax)
    plt.grid(True)
    plt.title(title)
    plt.legend()
    plt.yscale(scale)

    
    # Essa parte foi utilizada apenas para fazer o gráfico de total de comparações
    # da função de busca, por conta disso está comentada
    
    # x1, x2 = 4000, 6000
    # mask_avl = (data_avl[x] >= x1) & (data_avl[x] <= x2)
    # mask_rbt = (data_rbt[x] >= x1) & (data_rbt[x] <= x2)
    # y_min = min(data_avl[y][mask_avl].min(), data_rbt[y][mask_rbt].min())
    # y_max = max(data_avl[y][mask_avl].max(), data_rbt[y][mask_rbt].max())

    # axins = ax.inset_axes([0.5, 0.3, 0.3, 0.3])
    # sns.lineplot(x=data_avl[x], y=data_avl[y], color=color_avl, marker="o", ax=axins)
    # sns.lineplot(x=data_rbt[x], y=data_rbt[y], color=color_rbt, marker="o", ax=axins)
    # axins.set_xlim(x1, x2)
    # axins.set_ylim(y_min, y_max)
    # axins.set_xlabel("")
    # axins.set_ylabel("")
    # axins.set_xticklabels([])
    # axins.set_yticklabels([])

    # ax.indicate_inset_zoom(axins, edgecolor="black")
    plt.show()

make_lineplot("NumDocs", " totalInsertTime", "log", "#e60073", "green","blue")
make_lineplot("NumDocs", " totalHeight", "linear", '#e60073',"green", "blue")
make_lineplot("NumDocs", " totalSearchComp", "log", '#e60073',"green", "blue")
make_lineplot("NumDocs", " longestPath", "linear", '#e60073',"green", "blue")
make_lineplot("NumDocs", " avgInsertTime", "linear", '#e60073',"green", "blue")
make_lineplot("NumDocs", " avgSearchTime", "log", '#e60073',"green", "blue")
make_lineplot("NumDocs", " avgSearchComp", "linear", '#e60073',"green", "blue")
