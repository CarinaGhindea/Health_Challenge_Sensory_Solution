window.onload = function() {
    fetchData();
    setInterval(fetchData, 1000); // refreshes dashboard with new data every second 
}

async function fetchData() {
    try {
        const response = await fetch('/data'); // requests latest dashboard data from ESP32
        const data = await response.json(); // converts JSON response into JS object

        // .innerHTML sets the data to be displayed in the place of the HTML ID
        // functions ComfortLevelColour(...) update the colour of the text and/or 
        // card to reflect level or percentage to add a visual cue 
        document.getElementById("overall-comfort-text").innerHTML = data.overallComfort;
        updateOverallComfortLevelColourFromLevel(data.overallComfort);
        document.getElementById("recommendation-text").innerHTML = data.recommendation;

        document.getElementById("comfort-breakdown-text").innerHTML = data.comfortBreakdown + "%";
        updateOverallComfortLevelColourFromPercentage(data.comfortBreakdown);

        document.getElementById("light-breakdown-text").innerHTML = data.lightBreakdown + "%";
        updateComfortLevelColourFromPercentage("light-breakdown-card", data.lightBreakdown);
        document.getElementById("sound-breakdown-text").innerHTML = data.soundBreakdown + "%";
        updateComfortLevelColourFromPercentage("sound-breakdown-card", data.soundBreakdown);
        
        // displays "Not Connected" in place of inaccurate values when temperature sensor is not connected 
        // also updates colour of text and card for further visual aid 
        if (data.temperatureBreakdown === "Not Connected") {
            document.getElementById("temperature-breakdown-text").innerHTML = "Not Connected";
            updateComfortLevelColourFromPercentage("temperature-breakdown-card", data.temperatureBreakdown);
        }
        else {
            document.getElementById("temperature-breakdown-text").innerHTML = data.temperatureBreakdown + "%";
            updateComfortLevelColourFromPercentage("temperature-breakdown-card", data.temperatureBreakdown);
        }

        document.getElementById("light-level").innerHTML = "Level: " + data.lightLevel;
        document.getElementById("light-trend").innerHTML = "Trend: " + data.lightTrend;
        document.getElementById("light-spike").innerHTML = "Spike: " + data.lightSpike;
        updateComfortLevelColourFromLevel("light-info-card", data.lightLevel);

        document.getElementById("sound-level").innerHTML = "Level: " + data.soundLevel;
        document.getElementById("sound-trend").innerHTML = "Trend: " + data.soundTrend;
        document.getElementById("sound-spike").innerHTML = "Spike: " + data.soundSpike;
        updateComfortLevelColourFromLevel("sound-info-card", data.soundLevel);

        // displays "Not Connected" in place of inaccurate values when temperature sensor is not connected 
        // also updates colour of text and card for further visual aid 
        if (data.temperatureCurrent === "Not Connected") {
            document.getElementById("temperature-current").innerHTML = "Current Temperature: Not Connected";
            updateComfortLevelColourFromLevel("temperature-info-card", data.temperatureLevel);
        }
        else {
        document.getElementById("temperature-current").innerHTML = "Current Temperature: " + data.temperatureCurrent + "°C";
        updateComfortLevelColourFromLevel("temperature-info-card", data.temperatureLevel);
        }

        document.getElementById("temperature-level").innerHTML = "Level: " + data.temperatureLevel;
        document.getElementById("temperature-trend").innerHTML = "Trend: " + data.temperatureTrend;
        document.getElementById("temperature-spike").innerHTML = "Spike: " + data.temperatureSpike;

    }
    catch (error) {
        console.error('Error fetching data:', error);
    }
}

// corresponds with colours in CSS file and adds that colour to the card depending on level 
function updateComfortLevelColourFromLevel(elementId, level) {
    const comfortElement = document.getElementById(elementId);
    comfortElement.classList.remove("good", "moderate", "poor", "severe", "temperature-not-connected");

    if (level === "Good") {
        comfortElement.classList.add("good");
    } else if (level === "Moderate") {
        comfortElement.classList.add("moderate");
    } else if (level === "Poor") {
        comfortElement.classList.add("poor");
    } else if (level === "Severe") {
        comfortElement.classList.add("severe");
    } else {
        comfortElement.classList.add("temperature-not-connected")
    }
    
}

// corresponds with colours in CSS file and adds that colour to the card depending on percentage
function updateComfortLevelColourFromPercentage(elementId, percentage) {
    const comfortElement = document.getElementById(elementId);
    comfortElement.classList.remove("good", "moderate", "poor", "severe", "temperature-not-connected");

    if (percentage < 5.0) {
        comfortElement.classList.add("good");
    } else if (percentage < 10.0) {
        comfortElement.classList.add("moderate");
    } else if (percentage < 25.0) {
        comfortElement.classList.add("poor");
    } else if (percentage > 25.0) {
        comfortElement.classList.add("severe");
    } else {
        comfortElement.classList.add("temperature-not-connected")
    }
}

// corresponds with colours in CSS file and adds that colour to the overall comfort text depending on level 
function updateOverallComfortLevelColourFromLevel(level) {
    const comfortElement = document.getElementById("overall-comfort-text");
    comfortElement.classList.remove("good-text", "moderate-text", "poor-text", "severe-text");

    if (level === "Good") {
        comfortElement.classList.add("good-text");
    } else if (level === "Moderate") {
        comfortElement.classList.add("moderate-text");
    } else if (level === "Poor") {
        comfortElement.classList.add("poor-text");
    } else if (level === "Severe") {
        comfortElement.classList.add("severe-text");
    }
}

// corresponds with colours in CSS file and adds that colour to the overall comfort text depending on percentage 
function updateOverallComfortLevelColourFromPercentage(percentage) {
    const comfortElement = document.getElementById("comfort-breakdown-card");
    comfortElement.classList.remove("good", "moderate", "poor", "severe");

    if (percentage > 95.0) {
        comfortElement.classList.add("good");
    } else if (percentage > 90.0) {
        comfortElement.classList.add("moderate");
    } else if (percentage > 75.0) {
        comfortElement.classList.add("poor");
    } else {
        comfortElement.classList.add("severe");
    }
}