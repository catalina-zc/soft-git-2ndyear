import numpy as np
import matplotlib.pyplot as plt

def read_config(filename, skip=2):
    """Reading an vicsek configuration from a file handle"""
    with open(filename) as file_handle:
        # skip the first two lines
        for i in range(skip): 
            next(file_handle)

        data = np.loadtxt(file_handle)
        conf = {}

        conf["id"] = data[:,0]
        conf["x"] = data[:,1]
        conf["y"] = data[:,2]
        conf["theta"] = data[:,3]
        conf["vx"] = np.cos(conf["theta"])
        conf["vy"] = np.sin(conf["theta"])  
        return conf
    
def plot(conf,ax):
    qv = ax.quiver(conf["x"], conf["y"], conf["vx"], conf["vy"], conf["theta"], scale=1, scale_units='xy', cmap='hsv')
    plt.axis('equal')
    return qv

conf = read_config("init.conf")

fig, ax = plt.subplots()
plot(conf, ax)

plt.savefig("vicsek_arrows_png", writer = "ffmpeg", fps=30)