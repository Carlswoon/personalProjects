import React from 'react';

function Voting({ photos, setPhotos }) {
  const handleUpvote = (id) => {
    setPhotos((prevPhotos) =>
      prevPhotos.map((photo) =>
        photo.id === id ? { ...photo, votes: photo.votes + 1 } : photo
      )
    );
  };

  const handleDownvote = (id) => {
    setPhotos((prevPhotos) =>
      prevPhotos.map((photo) =>
        photo.id === id ? { ...photo, votes: photo.votes - 1 } : photo
      )
    );
  };

  // 🔥 Sort logic: votes > title > author
  const sortedPhotos = [...photos].sort((a, b) => {
    if (b.votes !== a.votes) return b.votes - a.votes;
    if (a.title.toLowerCase() !== b.title.toLowerCase()) return a.title.localeCompare(b.title);
    return a.author.localeCompare(b.author);
  });

  return (
    <div className="voting-container">
      {sortedPhotos.map((photo) => (
        <div key={photo.id} className="card">
          <img src={photo.src} alt={photo.title} className="photo" />
          <div className="card-info">
            <div className="vote-section">
              <button className="vote-btn" onClick={() => handleUpvote(photo.id)}>⬆️</button>
              <button className="vote-btn" onClick={() => handleDownvote(photo.id)}>⬇️</button>
              <span className="vote-count">{photo.votes !== 0 ? photo.votes : 'VOTE'}</span>
            </div>
            <h2 className="title">{photo.title}</h2>
            <p className="author">By {photo.author}</p>
          </div>
        </div>
      ))}
    </div>
  );
}

export default Voting;