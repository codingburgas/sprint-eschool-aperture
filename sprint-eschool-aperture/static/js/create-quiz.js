const quizButton = document.getElementById("quiz");
const lesson = document.getElementById("lesson-title");

quizButton.addEventListener("click", () => {
	document.location.href = "/quiz/" + lesson.innerText;
});