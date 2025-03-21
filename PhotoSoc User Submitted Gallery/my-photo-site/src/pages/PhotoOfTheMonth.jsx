import React from 'react';

function PhotoOfTheMonth({ photo }) {
  if (!photo) {
    return <div>No votes yet for Photo of the Month!</div>;
  }

  return (
    <div className="photo-of-the-month-card">
      <h1>Photo of the Month</h1>
      <img
        src={photo.src}
        alt={photo.title}
        className="photo-of-the-month-img"
      />
      <div className="photo-title">{photo.title}</div>
      <div className="photo-author">By {photo.author}</div>
      <p className="photo-votes">Votes: {photo.votes}</p>
    </div>
  );
}

export default PhotoOfTheMonth;