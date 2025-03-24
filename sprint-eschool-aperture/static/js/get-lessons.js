function getLessons() {
    fetch("/lessons/names/", {
		method: "GET"
	})
    .then(lessonNames => {
        console.log(lessonNames);
    });
}

getLessons();