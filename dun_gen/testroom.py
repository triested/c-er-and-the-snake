# Program to generate room shapes.
# Rooms are not always simple rectangles, but sometimes have cool shapes
# composed of *multiple* rectangles. What could be cooler than that?
# Author: Sam Champer


from random import randint


def neighbors(grid, maxdim, coords):
    # Function to return a list of neighbors of a square.
    tonari = []
    for x, y in [(coords[1] + i, coords[0] + j) for i in (-1, 0, 1) for j in (-1, 0, 1) if i != 0 or j != 0]:
        if x >= 0 and y >= 0 and y < maxdim and x < maxdim:
            tonari.append(grid[y][x])
    return tonari


def orthog_neighbors(grid, maxdim, coords):
    # Function to return a list of orthogonal neighbors.
    tonari = []
    for x, y in [(coords[1] + i, coords[0] + j) for i in (-1, 0, 1) for j in (-1, 0, 1)
                 if (i != 0 or j != 0) and (i == 0 or j == 0)]:
        if x >= 0 and y >= 0 and y < maxdim and x < maxdim:
            tonari.append(grid[y][x])
    return tonari


def set_location(grid, coords, value):
    # Function to set the value of a location.
    if coords[1] >= 0 and coords[0] >= 0 and coords [1] < len(grid) and coords[0] < len(grid):
        grid[coords[1]][coords[0]] = value


def padded_set_location(grid, coords, value):
    # Function to set the value of a location which does not have access to the outer two
    # rows and columns of the grid, since those need to be reserved for walls and paths.
    if coords[1] >= 2 and coords[0] >= 2 and coords[1] < len(grid) - 2 and coords[0] < len(grid) - 2:
        grid[coords[1]][coords[0]] = value
        return True


def get_location(grid, coords):
    # Return the value of a tile in the grid at a coordinate.
    if coords[1] >= 0 and coords[0] >= 0 and coords[1] < len(grid) and coords[0] < len(grid):
        return grid[coords[1]][coords[0]]
    else:
        return " "


def make_first_rect(grid, coords, value, width, height):
    # Makes a rectangle that is guaranteed to overlap with other stuff in the grid,
    # since the idea is to generate rooms that consist of overlapping rectangles.
    retval = False
    for y in range(coords[1] - int(width/2 + 0.5), coords[1] + int(width/2 + 0.5)):
        for x in range(coords[0] - int(height / 2 + 0.5), coords[1] + int(height / 2 + 0.5)):
            done_something = padded_set_location(grid, [x, y], value)
            if done_something:
                retval = True
    return retval


def make_rect(grid, coords, value, width, height):
    # Makes a rectangle that is guaranteed to overlap with other stuff in the grid,
    # since the idea is to generate rooms that consist of overlapping rectangles.
    overlap = False
    for y in range(coords[1] - int(width / 2 + 0.5), coords[1] + int(width / 2 + 0.5)):
        for x in range(coords[0] - int(height / 2 + 0.5), coords[1] + int(height / 2 + 0.5)):
            if get_location(grid, [x, y]) != " ":
                overlap = True
    if not overlap:
        return False

    for y in range(coords[1] - int(width/2 + 0.5), coords[1] + int(width/2 + 0.5)):
        for x in range(coords[0] - int(height / 2 + 0.5), coords[1] + int(height / 2 + 0.5)):
            padded_set_location(grid, [x, y], value)
    return True


def make_walls(grid):
    # Makes "#" walls around all the floor in the grid.
    # Then makes "R" walls around all the "#" walls. "R"
    # is reserved for making corridors between the rooms.
    maxdim = len(grid)
    for y in range(maxdim):
        for x in range(maxdim):
            if "." in neighbors(grid, maxdim, [y, x]) and get_location(grid, [x, y]) == " ":
                set_location(grid, [x, y], "#")

    for y in range(maxdim):
        for x in range(maxdim):
            if "#" in neighbors(grid, maxdim, [y, x]) and get_location(grid, [x, y]) == " ":
                set_location(grid, [x, y], "R")


def trim_room(grid):
    maxdim = len(grid)
    min_y = maxdim
    max_y = 0
    min_x = maxdim
    max_x = 0
    for y in range(maxdim):
        for x in range(maxdim):
            if get_location(grid, [x, y]) != " ":
                if y < min_y:
                    min_y = y
                if x < min_x:
                    min_x = x
                if y > max_y:
                    max_y = y
                if x > max_x:
                    max_x = x

    new_grid = [["~" for _ in range(max_x - min_x + 1)] for _ in range(max_y - min_y + 1)]
    for y in range(max_y - min_y + 1):
        for x in range(max_x - min_x + 1):
            new_grid[y][x] = grid[y + min_y][x + min_x]
    return new_grid


def make_doors(grid):
    height = len(grid)
    width = len(grid[0])
    num_doors = randint(1, 3)
    placed_doors = 0
    while placed_doors != num_doors:
        door_flavour = randint(1, 4)
        if door_flavour == 1:
            # Try to put door on column, looking from top.
            col = randint(0, width)
            # for i in range(height):
                # if grid   #TODO FIX DO

        elif door_flavour == 2:
            # Try to put door on column, looking from bottom.
            col = randint(0, width)

        elif door_flavour == 3:
            # Try to put door on row, looking from top.
            row = randint(0, height)

        elif door_flavour == 4:
            # Try to put door on row, looking from bottom.
            row = randint(0, height)


def make_room(floortype):
    # Function to make a random room with composed of a random number of rectangles.
    # Room will have random dimensions:
    maxdim = randint(8, 22)
    # Init grid
    grid = [[" " for _ in range(maxdim)]for _ in range(maxdim)]
    # Room is composed of some random number of rectangles.
    num_rects = randint(1, 4)
    i = 0
    while i < num_rects:
        # Generate a seed to start place the rectangle.
        seed = [randint(0, maxdim - 1), randint(0, maxdim - 1)]
        # Random size rect.
        rect_size = [randint(int(maxdim / num_rects), int((1.6 * maxdim) / num_rects)),
                     randint(int(maxdim / num_rects), int((1.6 * maxdim) / num_rects))]
        if i == 0:
            # For first rectangle.
            retval = make_first_rect(grid, [seed[1], seed[0]], floortype, rect_size[0], rect_size[1])
        else:
            retval = make_rect(grid, [seed[1], seed[0]], floortype, rect_size[0], rect_size[1])
        if retval:
            i += 1
    # Build walls around the room, and reserve
    # space around the walls for hallways.
    make_walls(grid)
    # Trim away unused space from the array.
    grid = trim_room(grid)

    # Rooms tend to generate in a certain way,
    # so lets randomly flip them around a bit:
    flip_x = randint(0, 1)
    flip_y = randint(0, 1)
    if flip_x:
        for row in grid:
            row = row[::-1]
    if flip_y:
        grid = grid[::-1]

    # Make some random doors in the room:
    make_doors(grid)

    return grid


def main():
    grid = make_room(".")
    for i in grid:
        for j in i:
            print(j, end="")
        print("")


if __name__ == "__main__":
    main()
