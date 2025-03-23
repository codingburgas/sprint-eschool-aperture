
function getLessonNames()
{

    fetch("/lessons/names/", {
		method: "GET"
	})
    .then((lessonNames) => {
         console.log(lessonNames);
     }) ;   
}
getLessonNames();