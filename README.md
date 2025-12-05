# AoC25
## Day 1
## Day 2
## Day 3
## Day 4
### --- Day 4: Printing Department ---

You ride the escalator down to the printing department. They're clearly getting ready for Christmas; they have lots of large rolls of paper everywhere, and there's even a massive printer in the corner (to handle the really big print jobs).

Decorating here will be easy: they can make their own decorations. What you really need is a way to get further into the North Pole base while the elevators are offline.

"Actually, maybe we can help with that," one of the Elves replies when you ask for help. "We're pretty sure there's a cafeteria on the other side of the back wall. If we could break through the wall, you'd be able to keep moving. It's too bad all of our forklifts are so busy moving those big rolls of paper around."

If you can optimize the work the forklifts are doing, maybe they would have time to spare to break through the wall.

The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input) indicating where everything is located.

For example:

..@@.@@@@.  
@@@.@.@.@@  
@@@@@.@.@@  
@.@@@@..@.  
@@.@@@@.@@  
.@@@@@@@.@  
.@.@.@.@@@  
@.@@@.@@@@  
.@@@@@@@@.  
@.@.@@@.@.  

The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent positions. If you can figure out which rolls of paper the forklifts can access, they'll spend less time looking and more time breaking down the wall to the cafeteria.

In this example, there are 13 rolls of paper that can be accessed by a forklift (marked with x):

..xx.xx@x.  
x@@.@.@.@@  
@@@@@.x.@@  
@.@@@@..@.  
x@.@@@@.@x  
.@@@@@@@.@  
.@.@.@.@@@  
x.@@@.@@@@  
.@@@@@@@@.  
x.x.@@@.x.  

Consider your complete diagram of the paper roll locations. How many rolls of paper can be accessed by a forklift?

Your puzzle answer was 1626.

The first half of this puzzle is complete! It provides one gold star: *
### --- Part Two ---

Now, the Elves just need help accessing as much of the paper as they can.

Once a roll of paper can be accessed by a forklift, it can be removed. Once a roll of paper is removed, the forklifts might be able to access more rolls of paper, which they might also be able to remove. How many total rolls of paper could the Elves remove if they keep repeating this process?

Starting with the same example as above, here is one way you could remove as many rolls of paper as possible, using highlighted @ to indicate that a roll of paper is about to be removed, and using x to indicate that a roll of paper was just removed:

Initial state:
..@@.@@@@.  
@@@.@.@.@@  
@@@@@.@.@@  
@.@@@@..@.  
@@.@@@@.@@  
.@@@@@@@.@  
.@.@.@.@@@  
@.@@@.@@@@  
.@@@@@@@@.  
@.@.@@@.@.  

Remove 13 rolls of paper:
..xx.xx@x.  
x@@.@.@.@@  
@@@@@.x.@@  
@.@@@@..@.  
x@.@@@@.@x  
.@@@@@@@.@  
.@.@.@.@@@  
x.@@@.@@@@  
.@@@@@@@@.  
x.x.@@@.x.  

Remove 12 rolls of paper:
.......x..  
.@@.x.x.@x  
x@@@@...@@  
x.@@@@..x.  
.@.@@@@.x.  
.x@@@@@@.x  
.x.@.@.@@@  
..@@@.@@@@  
.x@@@@@@@.  
....@@@...  

Remove 7 rolls of paper:
..........  
.x@.....x.  
.@@@@...xx  
..@@@@....  
.x.@@@@...  
..@@@@@@..  
...@.@.@@x  
..@@@.@@@@  
..x@@@@@@.  
....@@@...  

Remove 5 rolls of paper:
..........  
..x.......  
.x@@@.....  
..@@@@....  
...@@@@...  
..x@@@@@..  
...@.@.@@.  
..x@@.@@@x  
...@@@@@@.  
....@@@...  

Remove 2 rolls of paper:
..........  
..........  
..x@@.....  
..@@@@....  
...@@@@...  
...@@@@@..  
...@.@.@@.  
...@@.@@@.  
...@@@@@x.  
....@@@...  

Remove 1 roll of paper:
..........  
..........  
...@@.....  
..x@@@....  
...@@@@...  
...@@@@@..  
...@.@.@@.  
...@@.@@@.  
...@@@@@..  
....@@@...  

Remove 1 roll of paper:
..........  
..........  
...x@.....  
...@@@....  
...@@@@...  
...@@@@@..  
...@.@.@@.  
...@@.@@@.  
...@@@@@..  
....@@@...  

Remove 1 roll of paper:
..........  
..........  
....x.....  
...@@@....  
...@@@@...  
...@@@@@..  
...@.@.@@.  
...@@.@@@.  
...@@@@@..  
....@@@...  

Remove 1 roll of paper:
..........  
..........  
..........  
...x@@....  
...@@@@...  
...@@@@@..  
...@.@.@@.  
...@@.@@@.  
...@@@@@..  
....@@@...  

Stop once no more rolls of paper are accessible by a forklift. In this example, a total of 43 rolls of paper can be removed.

Start with your original diagram. How many rolls of paper in total can be removed by the Elves and their forklifts?

## Day5
### --- Day 5: Cafeteria ---

As the forklifts break through the wall, the Elves are delighted to discover that there was a cafeteria on the other side after all.

You can hear a commotion coming from the kitchen. "At this rate, we won't have any time left to put the wreaths up in the dining hall!" Resolute in your quest, you investigate.

"If only we hadn't switched to the new inventory management system right before Christmas!" another Elf exclaims. You ask what's going on.

The Elves in the kitchen explain the situation: because of their complicated new inventory management system, they can't figure out which of their ingredients are fresh and which are spoiled. When you ask how it works, they give you a copy of their database (your puzzle input).

The database operates on ingredient IDs. It consists of a list of fresh ingredient ID ranges, a blank line, and a list of available ingredient IDs. For example:

3-5  
10-14  
16-20  
12-18  

1  
5  
8  
11  
17  
32  

The fresh ID ranges are inclusive: the range 3-5 means that ingredient IDs 3, 4, and 5 are all fresh. The ranges can also overlap; an ingredient ID is fresh if it is in any range.

The Elves are trying to determine which of the available ingredient IDs are fresh. In this example, this is done as follows:

    Ingredient ID 1 is spoiled because it does not fall into any range.
    Ingredient ID 5 is fresh because it falls into range 3-5.
    Ingredient ID 8 is spoiled.
    Ingredient ID 11 is fresh because it falls into range 10-14.
    Ingredient ID 17 is fresh because it falls into range 16-20 as well as range 12-18.
    Ingredient ID 32 is spoiled.

So, in this example, 3 of the available ingredient IDs are fresh.

Process the database file from the new inventory management system. How many of the available ingredient IDs are fresh?


