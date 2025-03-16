// Select elements
const startButton = document.getElementById('startButton');
const startScreen = document.getElementById('startScreen');
const gameScreen = document.getElementById('gameScreen');

// Add event listener to the start button
startButton.addEventListener('click', () => {
    // Hide the start screen
    startScreen.style.display = 'none';
    // Show the game screen
    gameScreen.style.display = 'block';
});
