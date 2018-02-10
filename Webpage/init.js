var Module = {
  "print": function() {
    console.log(Array.prototype.slice.call(arguments).join(" "));
  },
  "printErr": function() {
    console.error(Array.prototype.slice.call(arguments).join(" "));
  },
  "canvas": document.querySelector("canvas")
};