import tkinter as tk
import math
import random
from tkinter import Tk
# from tkinter import Tk, Label
# from PIL import ImageTk, Image

filename = "graph_data.txt"
with open(filename, "r") as file:
    content = file.readlines()
    data_dict = {}
    for line in content:
        values = line.split(" ")
        key = values[0]
        dictionary_values = values[1:]
        data_dict[key] = dictionary_values

spname = "shortpath.txt"

with open(spname, "r") as file:
    nums = [float(num) for num in file.read().split()]
print(nums)



class GraphDisplay(tk.Canvas):
    def __init__(self, master, graph, sp, **kwargs):
        super().__init__(master, **kwargs)
        self.graph = graph
        # self.background_image = ImageTk.PhotoImage(background_image)
        self.dis_time = dis_time
        self.sp = sp
        self.node_radius = 20
        self.edge_width = 2
        self.node_positions = {}  # dictionary to store node positions

    def draw_graph(self):
        self.delete(tk.ALL)  # clear canvas
        # self.create_image(0, 0, anchor="nw", image=self.background_image)
        # Calculate node positions
        self.calculate_node_positions()
        # Draw edges
        for node, edges in self.graph.items():
            x1, y1 = self.node_positions[node]
            for alph in edges:
                if alph == '\n':
                    break
                x2, y2 = self.node_positions[alph]
                # if( (node == '3' and alph == '8') or (node == '8' and alph == '3')):
                #     self.create_line(x1, y1, x2, y2, width=self.edge_width, fill="blue")
                #     continue

                self.create_line(x1, y1, x2, y2, width=self.edge_width)
        # Draw nodes
        for node, position in self.node_positions.items():
            x, y = position
            count = 0
            n=0
            for snode in self.sp :       
                if node == snode:
                    count += 1
                    break
                   
            if(count == 1):
                self.create_oval(x - self.node_radius, y - self.node_radius,x + self.node_radius, y + self.node_radius,
                            fill='yellow', outline='black')
                
            else:
                self.create_oval(x - self.node_radius, y - self.node_radius,x + self.node_radius, y + self.node_radius,
                            fill='white', outline='black')
            self.create_text(x, y, text=str(node))
            # self.create_text(self.disx, self.disy, text=str(node))
            # self.create_text(self.timex, self.timey, text=str(node))
        self.draw_dis_time()  
    def draw_dis_time(self):
        dis_time_text = "Distance: {} Km \nTime: {} mins".format(self.dis_time[0], self.dis_time[1])
        x = self.winfo_width() - 10
        y = 10
        self.create_text(x, y, text=dis_time_text, anchor="ne", fill="black", font=("Arial", 12, "bold"))


    def calculate_node_positions(self):
        arr = [600,600,    #1
               720,650,    #2
               960,590,    #2
               790,490,    #3
               920,470,    #4
               590,350,    #5
               400,630,    #6
               740,270,    #7
               250,440,    #8
               290,200,    #9
               590,470,    #10
               850,70,     #11
               870,680,    #12
               935,770,    #13
               1170,470,   #14
               600,740,    #15
               950,320,    #16
               530,160,    #17
               1190,70,    #18
               950, 190 ]  #19
    
#                [ 190,95,    #baner
#                 1430,60,    #wagholi
#                 200,670,   #aeronaut.
#                 790,100,   #vishranwadi
#                 440,700,   #sinhgasd collg
#                 270,480,   #kothrud
#                 870,700,   #kondhwa
#                 950,200,   #aga khan
#                     #dhankwadi
#                 700,500,   #swargate
#                 200,250,   #pashan
#                 400,120,   #jupiterhosp
#                 1150,170,   #kharadi
#                 1070,500,  #magarpatta
#                 750,400,   #14
#                 750,400,   #15
#                 750,400,   #16
#                 630,360,   #ceophostel
#                 750,400,   #MP                  
#                 820,260]   #3 7 join
            
        width = self.winfo_width()
        height = self.winfo_height()
        num_nodes = len(self.graph)
        if num_nodes == 0:
            print("empty path")
            return 
        # angle = 2 * 3.14159 / num_nodes
        radius = min(width, height) * 0.4
        j=0
        for i, node in enumerate(self.graph.keys()):        
            # x = width / 2 - radius * math.cos(i * angle)
            # x = random.randint(100,1000)
            # y = random.randint(100, 500)
            x = arr[j] 
            # y = height / 2 - radius * math.sin(i * angle)
            y = arr[j+1]
            j+=2
            self.node_positions[node] = (x, y)
#             print(self.node_positions)
                     
        self.disx = width/2
        self.disy = height/2 - 10
        self.timex = width/2
        self.timey = height/2 + 10
    def resize(self, event):
        self.draw_graph()

# Example usage
if __name__ == "__main__":
    graph = data_dict
    sp = {}
    k = 0
    # while(k < len(nums)):
    #     if(k+1 == len(nums)):
    #         sp[str(nums[k])] = ""
    #         break
    #     sp[str(nums[k])] = str(nums[k+1])
    #     k += 1

    while(k < len(nums)):
        if(k+2 == len(nums)):
            sp[str(int(nums[k-3]))] = ["", "", ""]
            break
        sp[str(int(nums[k]))] = [str(int(nums[k+1])) , str(nums[k+2]), str(int(nums[k+3]))]
        k += 4
    dis_time = [str(nums[k+1]) , str(nums[k])]
    print(sp)
    # print(graph)
    print("\n")
    root = Tk()
    root.title('Route Optimizer')
    # background_image = Image.open("pune_map.png") 
    canvas = GraphDisplay(root, graph, sp, width=400, height=400)
    canvas.pack(fill=tk.BOTH, expand=True)
    canvas.draw_graph()
    canvas.bind("<Configure>", canvas.resize)
    
    root.mainloop()
