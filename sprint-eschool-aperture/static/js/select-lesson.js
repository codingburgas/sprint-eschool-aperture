const lessons = document.getElementById("lesson-list");
const lessonTitle = document.getElementById("lesson-title");
const editableContents = document.getElementById("editable");

lessons.addEventListener("click", event => {
	lessonTitle.innerText = event.target.innerText;

	fetch("/lessons/lesson/" + lessonTitle.innerText,{method: "GET"})
	.then(response => response.text())
	.then(lessonContent => {
    	editableContents.innerHTML = lessonContent;
	});
});