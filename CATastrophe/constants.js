export const config = {
  gridSize: 10,
  totalTiles: 100,
  playerImgSrc: './assets/images/player.png',
  frameSize: 64,
  framesPerRow: 3,
  directions: {
    w: { dx: 0, dy: -1, row: 3 }, // Up
    a: { dx: -1, dy: 0, row: 1 }, // Left
    s: { dx: 0, dy: 1, row: 0 }, // Down
    d: { dx: 1, dy: 0, row: 2 }, // Right
  },
};

