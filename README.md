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

Your puzzle answer was 635.

The first half of this puzzle is complete! It provides one gold star: *
### --- Part Two ---

The Elves start bringing their spoiled inventory to the trash chute at the back of the kitchen.

So that they can stop bugging you when they get new inventory, the Elves would like to know all of the IDs that the fresh ingredient ID ranges consider to be fresh. An ingredient ID is still considered fresh if it is in any range.

Now, the second section of the database (the available ingredient IDs) is irrelevant. Here are the fresh ingredient ID ranges from the above example:

3-5  
10-14  
16-20  
12-18  

The ingredient IDs that these ranges consider to be fresh are 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, and 20. So, in this example, the fresh ingredient ID ranges consider a total of 14 ingredient IDs to be fresh.

Process the database file again. How many ingredient IDs are considered to be fresh according to the fresh ingredient ID ranges?

## Day 6
### --- Day 6: Trash Compactor ---

After helping the Elves in the kitchen, you were taking a break and helping them re-enact a movie scene when you over-enthusiastically jumped into the garbage chute!

A brief fall later, you find yourself in a garbage smasher. Unfortunately, the door's been magnetically sealed.

As you try to find a way out, you are approached by a family of cephalopods! They're pretty sure they can get the door open, but it will take some time. While you wait, they're curious if you can help the youngest cephalopod with her math homework.

Cephalopod math doesn't look that different from normal math. The math worksheet (your puzzle input) consists of a list of problems; each problem has a group of numbers that need to be either added (+) or multiplied (*) together.

However, the problems are arranged a little strangely; they seem to be presented next to each other in a very long horizontal list. For example:

123 328  51 64   
 45 64  387 23   
  6 98  215 314  
*   +   *   +  

Each problem's numbers are arranged vertically; at the bottom of the problem is the symbol for the operation that needs to be performed. Problems are separated by a full column of only spaces. The left/right alignment of numbers within each problem can be ignored.

So, this worksheet contains four problems:

    123 * 45 * 6 = 33210  
    328 + 64 + 98 = 490  
    51 * 387 * 215 = 4243455  
    64 + 23 + 314 = 401  

To check their work, cephalopod students are given the grand total of adding together all of the answers to the individual problems. In this worksheet, the grand total is 33210 + 490 + 4243455 + 401 = 4277556.

Of course, the actual worksheet is much wider. You'll need to make sure to unroll it completely so that you can read the problems clearly.

Solve the problems on the math worksheet. What is the grand total found by adding together all of the answers to the individual problems?

Your puzzle answer was 5552221122013.

The first half of this puzzle is complete! It provides one gold star: *
### --- Part Two ---

The big cephalopods come back to check on how things are going. When they see that your grand total doesn't match the one expected by the worksheet, they realize they forgot to explain how to read cephalopod math.

Cephalopod math is written right-to-left in columns. Each number is given in its own column, with the most significant digit at the top and the least significant digit at the bottom. (Problems are still separated with a column consisting only of spaces, and the symbol at the bottom of the problem is still the operator to use.)

Here's the example worksheet again:

123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  

Reading the problems right-to-left one column at a time, the problems are now quite different:

    The rightmost problem is 4 + 431 + 623 = 1058
    The second problem from the right is 175 * 581 * 32 = 3253600
    The third problem from the right is 8 + 248 + 369 = 625
    Finally, the leftmost problem is 356 * 24 * 1 = 8544

Now, the grand total is 1058 + 3253600 + 625 + 8544 = 3263827.

Solve the problems on the math worksheet again. What is the grand total found by adding together all of the answers to the individual problems?



