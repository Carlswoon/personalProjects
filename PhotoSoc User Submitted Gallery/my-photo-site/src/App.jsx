import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import React from 'react';
import Header from './components/Header';
import Home from './pages/Home';
import Upload from './pages/Upload';
import Voting from './pages/Voting';
import PhotoOfTheMonth from './pages/PhotoOfTheMonth';

function App() {
  return (
    <Router>
      <Header />
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/upload" element={<Upload />} />
        <Route path="/voting" element={<Voting />} />
        <Route path="/photo-of-the-month" element={<PhotoOfTheMonth />} />
      </Routes>
    </Router>
  );
}

export default App;
