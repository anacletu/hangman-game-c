```markdown
# Hangman Game

A simple Hangman game written in C.

![Hangman Screenshot](screenshot.png)

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
- [How to Play](#how-to-play)
- [Acknowledgments](#acknowledgments)
- [Contributing](#contributing)
- [License](#license)

## Features

- Randomly selects a word from a list.
- Classic Hangman gameplay.
- Visual representation of the hangman.
- Tracks correct and incorrect guesses.
- Game over and victory conditions.
- Input validation for alphabetic characters.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- You have a C compiler (e.g., GCC) installed.

### Building

1. Clone the repository:

   ```sh
   git clone https://github.com/anacletu/hangman.git
   ```

2. Build the game:

   ```sh
   gcc hangman.c -o hangman
   ```

3. Run the game:

   ```sh
   ./hangman
   ```

## How to Play

1. Guess letters one at a time.
2. The game will display your correct guesses and the hangman's status.
3. You win if you guess the word or lose if the hangman is complete.

## Acknowledgments

- [Adapted Hangman ASCII art from this source](https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c).

## Contributing

Contributions are what make the open source community an amazing place to be. We welcome contributions from the community.

1. Fork the project.
2. Create your feature branch.
3. Commit your changes.
4. Push to the branch.
5. Open a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```