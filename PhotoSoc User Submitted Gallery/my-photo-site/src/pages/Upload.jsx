import React, { useState } from 'react';

function Upload({ addPhoto }) {
  const [title, setTitle] = useState('');
  const [author, setAuthor] = useState('');
  const [file, setFile] = useState(null);

  const handleFileChange = (e) => {
    setFile(e.target.files[0]);
  };

  const handleSubmit = (e) => {
    e.preventDefault();

    if (!title || !author || !file) {
      alert('Please fill out all fields and select an image.');
      return;
    }

    const newPhoto = {
      src: URL.createObjectURL(file), // Generate temporary URL for preview
      title,
      author
    };

    addPhoto(newPhoto);

    // Clear the form
    setTitle('');
    setAuthor('');
    setFile(null);
  };

  return (
    <div className="upload-container">
      <h1>Upload New Photo</h1>
      <form onSubmit={handleSubmit} className="upload-form">
        <input
          type="text"
          placeholder="Title"
          value={title}
          onChange={(e) => setTitle(e.target.value)}
        />
        <input
          type="text"
          placeholder="Author"
          value={author}
          onChange={(e) => setAuthor(e.target.value)}
        />
        <input type="file" accept="image/*" onChange={handleFileChange} />
        <button type="submit">Upload</button>
      </form>

      {/* Preview the image */}
      {file && (
        <div className="preview">
          <img src={URL.createObjectURL(file)} alt="Preview" />
        </div>
      )}
    </div>
  );
}

export default Upload;