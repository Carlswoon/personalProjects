import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import React, { useState } from 'react';
import Header from './components/Header';
import Home from './pages/Home';
import Upload from './pages/Upload';
import Voting from './pages/Voting';
import PhotoOfTheMonth from './pages/PhotoOfTheMonth';

function App() {
  const [photos, setPhotos] = useState([]);

  // Find the photo with the most votes
  const photoOfTheMonth = photos.reduce((topPhoto, currentPhoto) => {
    return currentPhoto.votes > (topPhoto?.votes || 0) ? currentPhoto : topPhoto;
  }, null);

  // ✅ Function to add a new photo
  const addPhoto = (newPhoto) => {
    setPhotos((prevPhotos) => [...prevPhotos, { ...newPhoto, id: prevPhotos.length + 1, votes: 0 }]);
  };

  return (
    <Router>
      <Header />
      <Routes>
        <Route path="/" element={<Home />} />
        {/* ✅ Pass addPhoto to Upload so users can add new photos */}
        <Route path="/upload" element={<Upload addPhoto={addPhoto} />} />
        <Route path="/voting" element={<Voting photos={photos} setPhotos={setPhotos} />} />
        <Route path="/photo-of-the-month" element={<PhotoOfTheMonth photo={photoOfTheMonth} />} />
      </Routes>
    </Router>
  );
}

export default App;