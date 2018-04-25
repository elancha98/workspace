var express = require('express');

var app = express();

// view engine setup
app.set('views', process.cwd() + '/views');
app.set('public', process.cwd() + '/public');
app.set('view engine', 'jade');

app.get('/', function (req, res) {
  res.render("index", {"title" : "HEXA-SNAKE"});
});

app.use(function (req, res)  {
  res.render("error", {"error" : {"status" : 404, "stack" : "Not found"}, "message" : "Invalid URL"});
});

//app.listen(3000);
module.exports = app;