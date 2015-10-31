var express = require('express');
var router = express.Router();
var sqlite3 = require('sqlite3').verbose();
var _=require('lodash');
var moment = require('moment');
/* GET users listing. */
router.get('/', function(req, res) {
  var db_name = "/Users/vinodg/Library/Developer/Xcode/DerivedData/udp_average_tracker-bxqiyzyqmssotyfdgquzmfqmpxjk/Build/Products/Debug/avg_tracker.db";
	var table = "TIMELOG";

	var dbpath = db_name;
	var db = new sqlite3.Database(dbpath, function(err){
		if (err) res.render('index', {title: 'Error: ' + err}); 
		return;
	});

	db.all(" select * from " + table, function(err, rows) {
			rows.slice(Math.max(rows.length - 50, 1));

	    rows = _.map(rows,function(row){

	    	return _.transform(row,function(result, val, key){
		    	if(key == 'time'){
		    		var t=moment.unix(val);
		    		result[key] = t.format();
		    	}else{
		    		result[key] = val;
		    	}
		    });
		  });

	    var message = "Viewing Timelog" ;
	    res.render('timelog', {message: message, rows: rows});
	    db.close();
	});

});

module.exports = router;
