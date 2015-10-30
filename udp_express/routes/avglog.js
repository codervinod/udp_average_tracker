var express = require('express');
var router = express.Router();
var sqlite3 = require('sqlite3').verbose();

/* GET users listing. */
router.get('/', function(req, res) {
  var db_name = "/Users/vinodg/Library/Developer/Xcode/DerivedData/udp_average_tracker-bxqiyzyqmssotyfdgquzmfqmpxjk/Build/Products/Debug/avg_tracker.db";
	var table = "AVERAGE_TIMELOG";

	var dbpath = db_name;
	var db = new sqlite3.Database(dbpath, function(err){
		if (err) res.render('index', {title: 'Error: ' + err}); 
		return;
	});

	db.all(" select * from " + table, function(err, rows) {	    
	    var message = "Viewing Average Timelog";
	    
	    res.render('avglog', {message: message, rows: rows});
	    db.close();
	});

});

module.exports = router;
