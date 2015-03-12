# baghchal
Desktop Baghchal application


Baghchal is a Nepali strategic board game of great national and cultural value, as well as creative merit. Games are an important part of any culture, and Nepal has some very interesting and unique ones, of which Baghchal is a good example. Seemingly simple, this board game nevertheless requires strong tactical play as well as deep positional insights for its mastery.

In this project, we have created a Baghchal game for 2 players, as well as a Baghchal engine with AI for playing Baghchal with the computer under various difficulty settings.

Rules:

One of the players chooses Tiger (Bagh) and the other chooses Goat (Bakhra). There are 4 tigers and 20 bakhras when the game starts.

The objective for each player is different. The goat side tries to trap all the tigers and prevent their movement. When the tigers have no legal move remaining, the goats win. On the other hand, the tigers have to capture 5 goats in order to win.

For a more detailed description of the rules and strategy of Baghchal, please visit this link.

Technical details:

The AI is coded with a simple algorithm employing a minimax search tree, with a static evaluation function, and alpha beta pruning. Nevertheless, it plays fairly well at the higher difficulty settings. The time taken by the AI to move varies from a fraction of a second to about half a minute depending upon the difficulty setting, and the complexity of the position.

It has a tendency to go into repetition sometimes (especially as goat) because in this version the repetition blocking algorithms have not been used. In any case, it is quite difficult to beat, and if you are a beginner, you will have to play and experiment a lot before finally winning a game.
Finally:

In the next version, the following changes are planned:

    The non-repetition rule will be employed.
    The AI will be made stronger, using a more accurate evaluation function, and possibly more depth in the search.
    The time that the AI takes to make a move will be made shorter.
    More sounds and animation will be added.

However, this does not mean that the game is not playable in this version. It is quite functional and entertaining.
