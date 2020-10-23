import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Circle
import matplotlib.animation as animation

def plot_environment():
    ob_x = 4
    ob_y = 3
    ob_1_x = 9
    ob_1_y = 6
    circle_2 = plt.Circle((ob_1_x, ob_1_y), radius = 1)
    fig, ax = plt.subplots()
    circle_1 = plt.Circle((ob_x, ob_y), radius = 1)
    ax.add_path(circle_1)
    plt.show()

# (2,10) (2,12) (2,14)
url_1 = "/home/ak/Documents/MovingGraphPython/Location_9999_0_0.txt"
url_2 = "/home/ak/Documents/MovingGraphPython/Location_9999_0_1.txt"
url_3 = "/home/ak/Documents/MovingGraphPython/Location_9999_0_2.txt"
print("This is working")
data_1 = np.loadtxt(url_1)
data_2 = np.loadtxt(url_2)
data_3 = np.loadtxt(url_3)
team_number = 16.0;
# agent_1 = (data_1[data_1[:,0] == team_number])
# agent_2 = (data_2[data_2[:,0] == team_number])
# agent_3 = (data_3[data_3[:,0] == team_number])
summation_data = [data_1[data_1[:,0] == team_number], data_2[data_2[:,0] == team_number], data_3[data_3[:,0] == team_number]]
print(summation_data[2][0][1])

# fig, ax  = plt.subplots()
# scat_1 = ax.scatter(agent_1[:,1],agent_1[:,2], color='red')
# scat_2 = ax.scatter(agent_2[:,1],agent_2[:,2], color='blue')
# scat_3 = ax.scatter(agent_3[:,1],agent_3[:,2], color='black')
# data = agent_1[:,1]
# y = agent_1[:,2]
# x_1 = agent_2[:,1]
# y_1 = agent_2[:,2]
# x_2 = agent_3[:,1]
# y_2 = agent_3[:,2]
#
# def update(num, x, y, x_1, y_1, x_2, y_2, sact_1, scat_2 , scat_3):
#     scat_1.set_data(x[:num], y[:num])
#     scat_2.set_data(x_1[:num], y_1[:num])
#     scat_3.set_data(x_2[:num], y_2[:num])
#     return scat_1,scat_2,scat_3
# #
# ani = animation.FuncAnimation(fig, update,  fargs=[x, y, x_1, y_1, x_2, y_2, line_1, line_2 , line_3], interval =50, blit = True)
# # plt.show()
# # plt.xlabel("X Coordinates")
# # plt.ylabel("Y Coordinates")
# # plt.title("Environment with UAV's moving")
# plt.show()
