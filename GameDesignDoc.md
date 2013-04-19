# Game Design Document

## Question 1
>You must tell us what 'things' you will have, how they will move (or not move). What they look like. Including the images in your document is an easy way to show us what they look like.

**Things I will have**

0. Main character: Dragon

1. Obstacle1: rock
<img src="./pics/obstacle1_rock.jpg" width="100" height="100" alt="Obstacle1_rock"/>

2. Obstacle2: arrow
<img src="./pics/obstacle2_arrow.jpg" width="100" height="100" alt="Obstacle2_arrow"/>

3. Obstacle3: fire ball
<img src="./pics/obstacle3_fireball.jpg" width="100" height="100" alt="Obstacle2_fireball"/>

4. Red bottle potion: HP potion
<img src="./pics/red_potion.jpg" width="100" height="100" alt="red_potion"/>

5. White bottle potion: invisible potion
<img src="./pics/white_potion.jpg" width="100" height="100" alt="white_potion"/>

**How they will move**
>Basicaly, dragon will be controlled by keyboard input; everytime user push arrow keyboards, dragon will move little bit to entered direction.
>Obstacle1, 2, and 3 as well as red and whith bottle potions will have different size, speed, and shape. They are going to be moved by using timer. 
0. Main character, which is a dragon, will be controlled by arrow key on a keyboard.
1. Obstacle1, which is a rock, will come up continuously and have a slow speed compared to the others
2. Obstacle2, which is an arrow, will move faster than rocks, 
3. Obstacle3, which is a fire ball, will have the biggest size among all obstacles and will have moderate speed in the middle between a rock and an arrow.
4. Red bottle potion, which is a HP potion, will recover dragon's HP. It will come up randomly.
5. White bottle potion, which is an invisible potion, will make dragon invisible so that any obstacles cannot give a dammage to the dragon while it is invisible.

## Question 2
>Tell us how to play your game. Is it mouse, or keyboard? If mouse, what do you do with the mouse. If keyboard, what key commands are there and what do they do.

## Question 3
>Tell us how the score changes. Can it go down?

## Question 4
>Tell us how you keep track of a player¡¯s lives. When do they lose one? When do they die?

## Question 5
>Show us the layout of your user interface. Tell us about menus, buttons, actions, and any other user interface components, and what they do.
>	-You should include pictures of what your interface would look like
>	-A photo of hand-drawn rendering would suffice. It does not need to be computer generated.




## Markdown
Markdown is a human-readable structured plain text format that is used to convert text into HTML. GitHub automatically renders Markdown into HTML.

This is a crash course on how to use Markdown. The following section will show you the plain text used to generate the document shown in the rendering section.

### Code

```
# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5

You can also write in **bold** or _italics_. You can also ~~strike through~~ or write inline `Code Segments`

>Blockquotes are done as such.

Just make sure to separate paragraphs with an emptyline. 
Otherwise, they are considered in the same paragraph.

You link to [Google](https://www.google.com) as such and lists are written has follows:
  1. First you indent with two empty spaces.
  1. Then, you use:
    * `1.` to signal an ordered (i.e. numbered) list, or
    * `*`, `-`, `+` to represent an unordered list.
      1. Make sure to maintain indentation
      1. As it is used to identify sub-lists
  1. Numbering and symboles don't matter as they are auto-generated later.

Tables are pretty easy to make:

| Tables        | Are           | Easy          |
| ------------- |:-------------:| -------------:|
| left-aligned  | centered      | right-aligned |
| header are    | bolded and    | centered      |
| zebra stripes | are neat      | 1             |


Images are added inline by using the following syntax
![alt text](http://octodex.github.com/images/Professortocat_v2.png "Image Title")
```

----

### Rendering
This section shows the rendering of the plain text above.

# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5

You can also write in **bold** or _italics_. You can also ~~strike through~~ or write inline `Code Segments`

>Blockquotes are done as such.

Just make sure to separate paragraphs with an emptyline. 
Otherwise, they are considered in the same paragraph.

You link to [Google](https://www.google.com) as such and lists are written has follows:
  1. First you indent with two empty spaces.
  1. Then, you use:
    * `1.` to signal an ordered (i.e. numbered) list, or
    * `*`, `-`, `+` to represent an unordered list.
      1. Make sure to maintain indentation
      1. As it is used to identify sub-lists
  1. Numbering and symboles don't matter as they are auto-generated later.

Tables are pretty easy to make:

| Tables        | Are           | Easy          |
| ------------- |:-------------:| -------------:|
| left-aligned  | centered      | right-aligned |
| header are    | bolded and    | centered      |
| zebra stripes | are neat      | 1             |


Images are added inline by using the following syntax
![alt text](http://octodex.github.com/images/Professortocat_v2.png "Image Title")

