const imageUpload = document.getElementById('image-upload');
const editableContent = document.getElementById('editable');

const reader = new FileReader();
reader.onload = () => {
    const img = document.createElement('img');
    img.src = reader.result;
    img.style.maxWidth = "300px"; // Limit image size
    img.style.display = "inline";
    editableContent.appendChild(img);
};

imageUpload.addEventListener('change', () => {
    const file = imageUpload.files[0];
    if (file) {
        reader.readAsDataURL(file);
    }
});