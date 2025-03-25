const lessonList = document.getElementById("lesson-list")

function loadLessons() {
    fetch("/lessons/names/", {method: "GET"})
    .then(response => response.json())
    .then(lessonNames => {
        lessonList.innerHTML = "";

        if (lessonNames) {
            for (let i = 1; i < lessonNames.length; i++) {
                lessonList.innerHTML += `<li>${lessonNames[i]}</li>`;
            }
        } else {
            lessonTitle.innerHTML = 'Add your first lesson by clicking the "+" button, then select your new lesson.';
        }
    });
}

loadLessons();