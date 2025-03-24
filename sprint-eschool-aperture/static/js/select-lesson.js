const lessons = document.getElementById("lesson-list");
const lessonTitle = document.getElementById("lesson-title");

lessons.addEventListener("click", event => {
	lessonTitle.innerText = event.target.innerText;
});