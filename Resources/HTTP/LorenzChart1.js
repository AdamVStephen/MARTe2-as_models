class LorenzChart1 extends MARTeObject {

    /**
     * NOOP
     */
    constructor() {
        super();
    }


    /**
     * Creates the canvas.
     *
     * @param {obj} target the target HTML container where to display the data.
     */
    prepareDisplay(target) {
        this.canvas = document.createElement("canvas");
        this.canvas.setAttribute("class", "pendulumCanvas");
        this.canvas.width = 500;
        this.canvas.height = 600;
        var ctx = this.canvas.getContext("2d");
        target.innerHTML = "";
        target.appendChild(this.canvas);

        var xlabel = "X"; 
        var ylabel = "Y";
        var xtype = "linear";
        var ytype = "linear";
        this.appendData  = true;
        var chart = new Chart(ctx, {
            // The type of chart we want to create
            type: "line",
            // The data for our dataset
            data: {
                datasets: [
                    {
                        label: "Data",
                        fill: "false",
                        backgroundColor: "white",
                        borderColor: "blue" // The main line color
                    }
                ]
            },
            // Configuration options go here
            options: {
                scales: {
                    xAxes: [{
                        type: xtype,
                        position: "bottom",
                        scaleLabel: {
                            display: true,
                            labelString: xlabel
                        },
			ticks : {
			    suggestedMin : -1.0,
			    suggestedMax : 1.0
			}
                    }],
                    yAxes: [{
                        type: ytype,
                        scaleLabel: {
                            display: true,
                            labelString: ylabel
                        },
			ticks : {
			    suggestedMin : -1.0,
			    suggestedmax : 1.0
			}

                    }]
                },
                responsive : false
            }
        });
        this.maxPoints = 100;
        chart.update();
        this.chart = chart;
        this.refresh(1);
    }

    /**
     * Plot the Lorenz Data
     *
     * @param {obj} jsonData the data as received by the server.
     */
    displayData(jsonData) {
        console.log(jsonData);
        //this.targetDivText.innerHTML = JSON.stringify(jsonData["InputSignals"], null, '\t');
        if (this.xx !== undefined && this.yy !== undefined) {
            var xval = jsonData["InputSignals"][this.xx];
            var yval = jsonData["InputSignals"][this.yy];
	    console.log("xval is " + xval);
	    console.log("yval is " + yval);
	    console.log("maxpoints is " + this.maxPoints);
            var data = this.chart.data.datasets[0].data;
	    console.log("length is " + data.length);
            if (data.length > this.maxPoints) {
                data.shift();
            }
            this.chart.data.datasets[0].data.push({x: xval, y: yval});
	    var rho = jsonData["Parameters"]["Rho"];
	    var sigma = jsonData["Parameters"]["Sigma"];
	    var beta = jsonData["Parameters"]["Beta"];
	    
	    this.chart.data.datasets[0].label = "Lorenz ( "
		+ rho + ", " + sigma + ", " + beta + 
		") " + data.length;
            this.chart.update();
	    
        }
    }

    reset() {
        this.chart.data.datasets[0].data = [];
        for (var i=0; i<this.chart.data.datasets.length; i++) {
            this.chart.data.datasets[i].data = [];
        }
    }

     setXSignal(xx) {
         this.xx = xx;
     }
          
     setYSignal(yy) {
         this.yy = yy;
     }

     setMaxPoints(maxPoints) {
         this.maxPoints = maxPoints;
     }
}

