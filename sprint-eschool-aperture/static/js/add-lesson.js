const addLessonsButton = document.getElementById("add");

addLessonsButton.addEventListener("click", () => {
	const fileName = prompt("Name your file:");
	fetch("/lessons/", {
		method: "POST",
		headers: {
			"Content-Type": "application/x-www-form-urlencoded"
		},
		body: `title=${encodeURIComponent(fileName)}`
	})
	.then(loadLessons());
});