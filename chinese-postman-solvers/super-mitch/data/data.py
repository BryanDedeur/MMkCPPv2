#pylint: skip-file
"""
Predefined graphs for testing and experimentation.

* Graphs are defined via lists containing tuples
* Each tuple in the list represents an edge
* Edges are defined as (start, end, length)

For example, an equilateral triangle like:

   1
  / \
 2 - 3

Would be represented as:

triangle = [(1, 2, 1), (2, 3, 1), (3, 1 ,1)]

"""

# Non-Eularian, single edge, 1-2
single = [(1,2,1)]

# Eularian, simple square, 1-2-3-4
square = [(1,2,1), (2,3,1), (3,4,1), (4,1,1)]

# Semi-Eularian, 2 triangles
ice_cream = [(1,2,4), (1,3,3), (1,4,5), (2,3,3), (3,4,5)]

# Non-Eularian, 3 triangles
sailboat = [
    (1,2,4), (1,3,3), (1,5,10), (2,3,2), (2,4,3), (3,4,3), (4,5,9)
]

# Semi-Eularian, 2 triangles w/ a tail
kite = [(1,2,4), (2,3,3), (3,4,2), (2,4,3), (5,4,2), (4,1,3)]

# Eularian, square w/ parallel edges
clover = [
    (1,2,1), (1,2,2), (2,3,1), (2,3,2), (3,4,1), (3,4,2), (4,1,1), (4,1,2)
]

# Non-eularian w/ 6 odd nodes
big_six = [
    (1,2,8), (1,5,4), (1,8,3), (2,3,9), (2,7,6), (3,4,5),
    (3,6,3), (4,5,5), (4,6,1), (5,6,2), (5,7,3), (7,8,1),
]

# Non-Eularian, 5 adjacent squares
ladder = [
    (1, 2,1), ( 1,12,1), ( 2, 3,1), (2,11,1), (3,4,1), (3,10,1),
    (4, 5,1), ( 4, 9,1), ( 5, 6,1), (5, 8,1), (6,7,1), (7, 8,1), (8,9,1),
    (9,10,1), (10,11,1), (11,12,1)
]

# North of University Ave to beaches
north = [
    ( 1, 2, 1), ( 2, 3, 1), ( 3, 4, 1), ( 3,25, 6), ( 2, 4, 1), ( 2,24, 7),
    ( 4, 5, 3), ( 5, 6, 1), ( 5,26, 6), ( 6, 7, 1), ( 6, 8, 1), ( 8, 9,12),
    ( 8,26, 7), ( 9,10, 5), ( 9,19, 4), (10,11, 1), (10,19, 1), (10,12, 2),
    (12,13, 4), (12,18, 1), (13,14, 1), (13,15, 1), (13,16, 4),
    (17,18, 8), (18,19, 1), (18,20, 1),
    (19,20, 1), (20,21, 5), (21,22, 1), (22,23, 1), (22,24, 5), (21,25,4),
    (24,25, 3), (25,26, 1), (26,27, 1)
]

# Entirety of Pacific Spirit Park!
pacific_spirit = [
    ( 1, 2, 1), ( 2, 3, 1), ( 3, 4, 1), ( 3,25, 6), ( 2, 4, 1), ( 2,24, 7),
    ( 4, 5, 3), ( 5, 6, 1), ( 5,26, 6), ( 6, 7, 1), ( 6, 8, 1), ( 8, 9,12),
    ( 8,26, 7), ( 9,10, 5), ( 9,19, 4), (10,11, 1), (10,19, 1), (10,12, 2),
    (12,13, 4), (12,18, 1), (13,14, 1), (13,15, 1), (13,16, 4), (16,31, 1),
    (31,30, 2), (30,94, 2), (94,17, 1), (17,18, 8), (18,19, 1), (18,20, 1),
    (19,20, 1), (20,21, 5), (21,22, 1), (21,25, 4), (22,23, 1), (22,24, 5),
    (24,25, 3), (25,26, 1), (26,27, 1), (28,103,3), (28,36, 4), (28,40, 1),
    (16,32, 1), (32,33, 1), (32,31, 1), (32,35, 3), (31,34, 2), (34,30, 1),
    (34,36, 1), (30,29, 3), (29,28, 1), (29,103,5), (29,95, 1), (17,95, 3),
    (94,95, 3), (96,103,2), (96,100,1), (96,101,1), (97,100,1), (98,100,1),
    (98,99, 1), (98,101,1), (101,102,1), (95,96,6), (41,103,1), (36,39, 1),
    (35,36, 1), (35,38, 1), (38,37, 1), (38,39, 1), (39,40, 4), (39,59, 2),
    (40,58, 3), (40,41, 3), (41,42, 3),
    (41,58, 2), (42,43, 1), (43,44, 2), (44,45, 1), (44,46, 1), (43,46, 2),
    (45,46, 1), (46,47, 1), (45,47, 1), (47,48, 3), (48,49, 3), (48,55, 1),
    (45,49, 1),
    (49,50, 4), (49,51,10), (51,52, 1), (51,90, 6), (51,91, 2), (48,52, 6),
    (52,53, 4), (53,54, 1), (53,92, 3), (54,55, 1), (54,60, 4), (55,56, 3),
    (42,56, 5), (56,57, 1), (57,58, 3), (57,60, 2), (60,61, 2), (61,62, 1),
    (61,65, 2), (62,59, 6), (62,63, 2), (63,64, 1), (63,65, 2), (64,68, 2),
    (64,70, 2), (59,70, 7), (70,71, 1), (71,72, 1), (38,71, 7), (71,74, 3),
    (74,73, 1), (74,69, 1), (69,70, 2), (68,69, 1), (67,68, 3), (66,67, 1),
    (66,78, 5), (65,66, 3), (53,65, 4), (66,93, 2), (67,77, 3), (68,77, 1),
    (69,75, 1), (75,76, 2), (75,77, 1), (75,79, 2), (77,78, 2), (78,79, 1),
    (79,80, 2), (79,81, 6), (81,82, 1), (81,83,16), (83,84, 5), (83,86, 1),
    (84,85, 1), (85,86, 4), (85,87, 6), (86,87, 6), (86,93,14), (87,88, 1),
    (87,89, 4), (87,90, 4), (90,91, 6), (91,92, 1), (92,93, 1)
]

# Number of odd vertices:  4
gdb1 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 10, 19), (1, 12, 4), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (5, 6, 7), (5, 11, 20), (5, 12, 11), (6, 7, 4), (6, 12, 3), (7, 8, 8), (7, 12, 18), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12),
]

# Number of odd vertices:  6
gdb2 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 9, 11), (1, 10, 19), (1, 12, 4), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (4, 12, 5), (5, 6, 7), (5, 11, 20), (5, 12, 11), (6, 7, 4), (6, 8, 14), (6, 12, 3), (7, 8, 8), (7, 10, 9), (7, 12, 18), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12),
]

# Number of odd vertices:  4
gdb3 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 9, 11), (1, 10, 19), (1, 12, 4), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (3, 12, 6), (5, 6, 7), (5, 11, 20), (5, 12, 11), (6, 7, 4), (6, 12, 3), (7, 8, 8), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12),
]

# Number of odd vertices:  3
gdb4 = [
(1, 2, 13), (1, 4, 17), (1, 6, 4), (1, 7, 19), (1, 10, 19), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (5, 6, 11), (5, 11, 20), (7, 6, 18), (7, 8, 8), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12),
]

# Number of odd vertices:  6
gdb5 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 10, 19), (1, 12, 4), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (3, 13, 22), (4, 13, 6), (5, 6, 7), (5, 11, 20), (5, 12, 11), (5, 13, 17), (6, 7, 4), (6, 12, 3), (7, 8, 8), (7, 12, 18), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12), (12, 13, 19),
]

# Number of odd vertices:  8
gdb6 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 10, 19), (1, 12, 4), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (3, 11, 22), (4, 11, 6), (5, 6, 7), (5, 11, 17), (5, 12, 11), (6, 7, 4), (6, 12, 3), (7, 8, 8), (7, 12, 18), (8, 10, 3), (9, 10, 16), (12, 11, 19),
]

# Number of odd vertices:  2
gdb7 = [
(1, 2, 13), (1, 4, 17), (1, 7, 19), (1, 10, 19), (1, 11, 17), (1, 12, 4), (2, 3, 18), (2, 4, 9), (2, 9, 2), (3, 4, 20), (3, 5, 5), (5, 11, 20), (5, 12, 11), (6, 7, 4), (6, 11, 3), (7, 8, 8), (7, 12, 18), (8, 10, 3), (8, 11, 10), (9, 10, 16), (9, 11, 14), (10, 11, 12),
]

# Number of odd vertices:  12
gdb8 = [
(1, 3, 7), (1, 15, 8), (1, 17, 5), (1, 19, 1), (1, 24, 6), (1, 27, 7), (2, 1, 3), (2, 12, 1), (3, 4, 7), (3, 6, 4), (3, 8, 6), (4, 5, 2), (4, 6, 7), (4, 10, 1), (5, 6, 2), (5, 9, 3), (6, 7, 3), (6, 8, 6), (6, 9, 6), (6, 10, 2), (7, 11, 6), (8, 9, 6), (10, 11, 5), (12, 13, 4), (13, 14, 4), (13, 15, 4), (14, 16, 9), (14, 18, 2), (14, 20, 5), (14, 21, 5), (15, 17, 3), (15, 20, 8), (16, 17, 9), (18, 21, 2), (18, 25, 3), (20, 21, 1), (21, 22, 8), (21, 23, 7), (21, 25, 8), (22, 23, 1), (22, 25, 3), (23, 24, 5), (23, 26, 3), (24, 27, 5), (25, 26, 4), (26, 27, 3),
]

# Number of odd vertices:  11
gdb9 = [
(1, 3, 7), (1, 15, 8), (1, 17, 5), (1, 19, 1), (1, 24, 6), (1, 27, 7), (2, 1, 3), (2, 12, 1), (3, 4, 7), (3, 6, 4), (3, 8, 6), (4, 5, 2), (4, 6, 7), (4, 10, 1), (4, 12, 1), (4, 19, 3), (5, 6, 2), (5, 9, 3), (6, 7, 3), (6, 8, 6), (6, 9, 6), (6, 10, 2), (7, 11, 6), (8, 9, 6), (8, 24, 2), (8, 27, 1), (10, 11, 5), (12, 13, 4), (12, 19, 2), (13, 14, 4), (13, 15, 4), (14, 16, 9), (14, 18, 2), (14, 20, 5), (14, 21, 5), (15, 17, 3), (15, 20, 8), (16, 17, 9), (18, 21, 2), (18, 25, 3), (20, 21, 1), (21, 22, 8), (21, 23, 7), (21, 25, 8), (22, 23, 1), (22, 25, 3), (23, 24, 5), (23, 26, 3), (24, 27, 5), (25, 26, 4), (26, 27, 3),
]

# Number of odd vertices:  7
gdb10 = [
(1, 8, 9), (1, 9, 4), (1, 10, 13), (1, 11, 12), (2, 1, 11), (2, 3, 15), (2, 4, 18), (2, 5, 8), (3, 4, 8), (3, 8, 18), (3, 9, 6), (4, 1, 7), (4, 6, 10), (4, 11, 17), (5, 1, 9), (5, 6, 15), (6, 11, 3), (7, 2, 6), (7, 4, 11), (7, 5, 5), (8, 9, 14), (8, 12, 5), (9, 10, 19), (10, 12, 2), (11, 12, 7),
]

# Number of odd vertices:  13
gdb11 = [
(1, 8, 9), (1, 9, 4), (1, 10, 13), (1, 11, 12), (2, 1, 11), (2, 3, 15), (2, 4, 18), (2, 5, 8), (2, 22, 2), (3, 4, 8), (3, 8, 18), (3, 9, 6), (3, 21, 2), (4, 1, 7), (4, 6, 10), (4, 11, 17), (5, 1, 9), (5, 6, 15), (5, 14, 2), (6, 11, 3), (6, 15, 2), (7, 2, 6), (7, 4, 11), (7, 5, 5), (7, 13, 2), (8, 9, 14), (8, 12, 5), (8, 20, 2), (9, 10, 19), (9, 19, 2), (10, 12, 2), (10, 18, 2), (11, 12, 7), (11, 16, 2), (12, 17, 2), (13, 14, 5), (13, 22, 6), (14, 15, 15), (15, 16, 3), (16, 17, 7), (17, 18, 2), (18, 19, 19), (19, 20, 6), (20, 21, 6), (21, 22, 15),
]

# Number of odd vertices:  7
gdb12 = [
(1, 2, 5), (1, 3, 7), (1, 4, 10), (1, 5, 19), (2, 3, 16), (2, 6, 8), (2, 7, 9), (2, 8, 14), (3, 6, 11), (4, 5, 11), (4, 10, 26), (4, 11, 30), (5, 10, 3), (6, 10, 13), (6, 12, 17), (7, 9, 30), (8, 9, 18), (8, 12, 21), (9, 13, 8), (10, 11, 15), (11, 12, 19), (11, 13, 12), (12, 13, 14),
]

# Number of odd vertices:  4
gdb13 = [
(1, 5, 7), (1, 6, 18), (1, 7, 4), (1, 8, 24), (1, 9, 11), (2, 1, 15), (2, 3, 5), (2, 5, 12), (2, 8, 13), (3, 1, 8), (3, 6, 1), (3, 7, 10), (3, 8, 24), (4, 1, 6), (4, 2, 3), (4, 3, 28), (4, 5, 2), (5, 6, 20), (5, 7, 42), (5, 9, 12), (6, 7, 9), (6, 9, 13), (7, 8, 16), (7, 9, 60), (7, 10, 5), (8, 9, 22), (8, 10, 99), (9, 10, 20),
]

# Number of odd vertices:  3
gdb14 = [
(1, 2, 1), (1, 3, 2), (1, 4, 7), (1, 5, 2), (1, 6, 5), (1, 7, 4), (2, 3, 6), (2, 4, 4), (2, 5, 1), (2, 6, 7), (2, 7, 7), (3, 4, 8), (3, 5, 1), (3, 6, 5), (3, 7, 7), (4, 5, 4), (4, 6, 4), (4, 7, 6), (5, 6, 7), (5, 7, 5), (6, 7, 3),
]

# Number of odd vertices:  3
gdb15 = [
(1, 2, 1), (1, 3, 1), (1, 4, 1), (1, 5, 1), (1, 6, 1), (1, 7, 1), (2, 3, 2), (2, 4, 2), (2, 5, 2), (2, 6, 2), (2, 7, 2), (3, 4, 3), (3, 5, 3), (3, 6, 3), (3, 7, 3), (4, 5, 4), (4, 6, 4), (4, 7, 4), (5, 6, 5), (5, 7, 5), (6, 7, 6),
]

# Number of odd vertices:  4
gdb16 = [
(1, 2, 4), (1, 3, 1), (1, 4, 3), (1, 5, 6), (1, 6, 6), (1, 7, 2), (1, 8, 1), (2, 3, 3), (2, 4, 6), (2, 5, 4), (2, 6, 2), (2, 7, 6), (2, 8, 4), (3, 4, 7), (3, 5, 3), (3, 6, 4), (3, 7, 8), (3, 8, 2), (4, 5, 6), (4, 6, 2), (4, 7, 4), (4, 8, 1), (5, 6, 6), (5, 7, 2), (5, 8, 8), (6, 7, 8), (6, 8, 3), (7, 8, 7),
]

# Number of odd vertices:  4
gdb17 = [
(1, 2, 1), (1, 3, 1), (1, 4, 1), (1, 5, 1), (1, 6, 1), (1, 7, 1), (1, 8, 1), (2, 3, 2), (2, 4, 2), (2, 5, 2), (2, 6, 2), (2, 7, 2), (2, 8, 2), (3, 4, 3), (3, 5, 3), (3, 6, 3), (3, 7, 3), (3, 8, 3), (4, 5, 4), (4, 6, 4), (4, 7, 4), (4, 8, 4), (5, 6, 5), (5, 7, 5), (5, 8, 5), (6, 7, 6), (6, 8, 6), (7, 8, 7),
]

# Number of odd vertices:  4
gdb18 = [
(1, 2, 3), (1, 3, 5), (1, 4, 6), (1, 5, 6), (1, 6, 4), (1, 7, 4), (1, 8, 5), (1, 9, 8), (2, 3, 6), (2, 4, 1), (2, 5, 3), (2, 6, 7), (2, 7, 4), (2, 8, 5), (2, 9, 4), (3, 4, 5), (3, 5, 7), (3, 6, 7), (3, 7, 7), (3, 8, 7), (3, 9, 3), (4, 5, 5), (4, 6, 3), (4, 7, 1), (4, 8, 1), (4, 9, 3), (5, 6, 7), (5, 7, 4), (5, 8, 7), (5, 9, 8), (6, 7, 6), (6, 8, 1), (6, 9, 1), (7, 8, 1), (7, 9, 2), (8, 9, 1),
]

# Number of odd vertices:  3
gdb19 = [
(1, 2, 4), (1, 4, 3), (1, 5, 1), (1, 6, 2), (2, 3, 1), (2, 4, 9), (2, 5, 5), (2, 7, 2), (5, 7, 7), (6, 8, 5), (7, 3, 6),
]

# Number of odd vertices:  2
gdb20 = [
(1, 3, 2), (1, 4, 3), (1, 5, 4), (1, 7, 1), (1, 8, 9), (1, 9, 1), (2, 5, 6), (2, 9, 2), (3, 7, 7), (3, 10, 7), (4, 7, 4), (4, 8, 9), (4, 9, 6), (5, 6, 7), (5, 7, 2), (5, 8, 8), (5, 11, 7), (7, 8, 3), (7, 10, 4), (7, 11, 4), (8, 9, 7), (8, 10, 2),
]

# Number of odd vertices:  5
gdb21 = [
(1, 2, 1), (1, 3, 7), (1, 5, 8), (1, 6, 6), (1, 7, 3), (1, 8, 2), (1, 9, 4), (1, 10, 2), (1, 11, 1), (2, 3, 1), (2, 4, 2), (2, 5, 4), (2, 6, 4), (2, 8, 1), (2, 9, 6), (3, 5, 6), (3, 6, 9), (3, 10, 3), (3, 11, 6), (4, 7, 8), (4, 8, 9), (4, 9, 8), (5, 7, 4), (6, 7, 8), (6, 9, 4), (6, 10, 7), (6, 11, 3), (7, 8, 3), (7, 9, 6), (7, 10, 3), (7, 11, 2), (8, 10, 1), (9, 10, 7),
]

# Number of odd vertices:  4
gdb22 = [
(1, 2, 6), (1, 3, 1), (1, 4, 2), (1, 5, 1), (1, 6, 1), (1, 7, 1), (1, 8, 1), (1, 9, 2), (1, 10, 3), (1, 11, 3), (2, 3, 5), (2, 4, 1), (2, 5, 8), (2, 7, 1), (2, 8, 1), (2, 9, 8), (2, 11, 5), (3, 4, 6), (3, 5, 3), (3, 7, 1), (3, 9, 9), (3, 10, 1), (3, 11, 8), (4, 5, 7), (4, 6, 6), (4, 7, 7), (4, 8, 7), (4, 9, 1), (4, 10, 8), (4, 11, 3), (5, 7, 6), (5, 8, 1), (5, 10, 6), (5, 11, 8), (6, 7, 5), (6, 8, 8), (6, 9, 5), (6, 10, 6), (7, 9, 6), (7, 10, 2), (7, 11, 1), (8, 9, 9), (9, 10, 7), (9, 11, 4),
]

# Number of odd vertices:  5
gdb23 = [
(1, 2, 1), (1, 3, 7), (1, 4, 1), (1, 5, 3), (1, 6, 3), (1, 7, 2), (1, 8, 1), (1, 9, 2), (1, 10, 2), (1, 11, 1), (2, 3, 5), (2, 4, 1), (2, 5, 8), (2, 6, 1), (2, 7, 3), (2, 8, 7), (2, 9, 8), (2, 10, 7), (2, 11, 2), (3, 4, 7), (3, 5, 1), (3, 6, 4), (3, 7, 1), (3, 8, 5), (3, 9, 4), (3, 10, 2), (3, 11, 2), (4, 5, 2), (4, 6, 1), (4, 7, 5), (4, 8, 7), (4, 9, 6), (4, 10, 2), (4, 11, 4), (5, 6, 8), (5, 7, 5), (5, 8, 4), (5, 9, 8), (5, 10, 6), (5, 11, 7), (6, 7, 5), (6, 8, 3), (6, 9, 6), (6, 10, 6), (6, 11, 4), (7, 8, 2), (7, 9, 1), (7, 10, 6), (7, 11, 4), (8, 9, 4), (8, 10, 5), (8, 11, 6), (9, 10, 4), (9, 11, 7), (10, 11, 4),
]