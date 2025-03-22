document.getElementById('imageUpload').addEventListener('change', function(event) {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const img = document.createElement('img');
            img.src = e.target.result;
            img.style.maxWidth = "300px"; // Limit image size
            img.style.display = "inline";
            document.querySelector('.editable').appendChild(img);
        };
        reader.readAsDataURL(file);
    }
});
