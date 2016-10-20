![A terrarium in action](https://github.com/rmmanseau/terra/blob/master/conf/assets/screenshots/terra-in-action.gif)

Terra
======
Terra lets you create and watch the interactions between creatures in a virtual terrarium. This projects inspiration comes from a textbook called [Eloquent Javascript](http://eloquentjavascript.net/07_elife.html)

Meet the Creatures
------------------
Creatures/Entities are defined as bundles of components. The components that make up an entity are defined in YAML, allowing for entities to be created and edited on the fly.

![Rock](https://github.com/rmmanseau/terra/blob/master/conf/assets/screenshots/rock.png)

This is a rock. It does nothing but take up space.

![Grass](https://github.com/rmmanseau/terra/blob/master/conf/assets/screenshots/grass.png)

This is a patch of grass. It takes in energy and when it has enough stored up will grow new grass next to it. If a patch of grass has too many entities surrounding it, it becomes suffocated and dies.

![Bug](https://github.com/rmmanseau/terra/blob/master/conf/assets/screenshots/bug.png)

This is a dumb bug. It moves at random, hoping to come across grass to eat. If the bug finds a lot of grass, it builds up enough energy to lay an egg. If the bug can't find any grass, it starves.

![Egg](https://github.com/rmmanseau/terra/blob/master/conf/assets/screenshots/egg.png)

This is an egg. Eventually, it hatches into a dumb bug.

Libraries
---------
  - [YAML](http://www.yaml.org/) is used for storing entity info.
  - [SFML](http://www.sfml-dev.org/) is used to print graphics.
