import matplotlib.pyplot as plt



def plot_line(slope, intercept, x_range):
    # calculate y values for given x range
    y_range = [slope * x + intercept for x in x_range]
    # plot the line
    plt.plot(x_range, y_range)
    # plt.show()


# Open the text file and read its contents
with open("task2printer.txt", "r") as f:
    contents = f.readlines()

# Extract the number of points from the first line
num_points = int(contents[0])

# Create empty lists to store the x and y coordinates
x_coords = []
y_coords = []

# Iterate through each line in the file (excluding the first line)
for line in contents[1:num_points+1]:
    # Split the line into two strings representing the x and y coordinates
    x, y = line.split()

    # Convert the strings to floats and add them to the x and y coordinate lists
    x_coords.append(float(x))
    y_coords.append(float(y))

# Create a scatter plot of the points
plt.scatter(x_coords, y_coords)

# with open("output.txt", "r") as f:
#     contents = f.readlines()


# Open the text file and read its contents
with open("task2printer.txt", "r") as f:
    lines = f.readlines()

# Extract the number of points from the first line
segments = int(lines[num_points+1])

for line in lines[num_points+2:segments+2+num_points]:
    slope, intercept,x1, x2= line.split()
    
    x_values = [float(x1),float(x2)]
    # print(x_values)
    plot_line(float(slope),float(intercept),x_values)
    






# slope = 2
# intercept = 5
# x_range = range(-10, 11)

# plot_line(slope, intercept, x_range)

plt.show()
