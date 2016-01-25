# Playing with CQRS and Event Sourcing

On Jan 14th
the group <a href="http://www.meetup.com/Software-Craftsmanship-Meetup-Softwerkskammer-Munchen/events/227376769/">
Softwerkskammer Munich</a> organized another awesome meetup, and the topic was CRQS (Command Query Responsability 
Segregation) and Event Sourcing, which were unknown to me.

After a brief explanation by <a href="https://github.com/hovinen">Bradford Hovinen</a>, we started our Kata, described
<a href="https://github.com/hovinen/softwerkskammer-muenchen-01-2016">here</a>, but I confess I spent most of time
setting up (unsuccessfuly) Eclipse to open the Graddle project, I decided to implement it as a "homework", but in C++
instead of Java, as I am not really a fan of Java and my C++ skills has became a bit rusty lately, so it was also a great
opportunity to practise it again.

I didn't fucused on all aspects of the original description, so a lot of things are missing.

What does this code do so far?

- Add items to the "singleton" (there is only one list per service) shopping list
- Removes items
- Infinite undo's (Yay!)
- Unit tests for all operations

## TODO

- Notification system
- REST interface
- Action Validation
- Separation between Read and Write repository
- "Strike" operation

## Running it 

Unfortunately there is no "main" executable yet. So far there is only unit test code.
After cloning the repository, compile and run the tests with:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make && make tests
```

For a "pretty" tests output, run:

```bash
./tests/shopping_tests --reporter=spec
```
