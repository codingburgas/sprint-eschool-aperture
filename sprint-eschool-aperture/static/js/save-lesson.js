const saveButton = document.getElementById("save");
const contents = document.getElementById("editable");
const titleLesson = document.getElementById("lesson-title");

saveButton.addEventListener("click", () => {
const lesson = {
    "lessonTitle": titleLesson.innerText,
     "lessonContent": contents.innerHTML

};

    fetch("/lessons/", {
		method: "PUT",
		headers: {
			"Content-Type": "application/json"
		},
		body: JSON.stringify(lesson)

	})
    .then(alert("The lesson has been saved"));
});
