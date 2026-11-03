window.onload = function() {
    fetchData();
}

async function fetchData() {
    try {
        const response = await fetch('/data');
        const data = await response.json();

        document.getElementById("overall-comfort-text").innerHTML = data.overallComfort;
        document.getElementById("recommendation-text").innerHTML = data.recommendation;

        document.getElementById("comfort-breakdown-text").innerHTML = data.comfortBreakdown;

        document.getElementById("light-breakdown-text").innerHTML = data.lightBreakdown;
        document.getElementById("sound-breakdown-text").innerHTML = data.soundBreakdown;
        document.getElementById("temperature-breakdown-text").innerHTML = data.temperatureBreakdown;

        document.getElementById("light-level").innerHTML = data.lightLevel;
        document.getElementById("light-trend").innerHTML = data.lightTrend;
        document.getElementById("light-spike").innerHTML = data.lightSpike;

        document.getElementById("sound-level").innerHTML = data.soundLevel;
        document.getElementById("sound-trend").innerHTML = data.soundTrend;
        document.getElementById("sound-spike").innerHTML = data.soundSpike;

        document.getElementById("temperature-current").innerHTML = data.temperatureCurrent;
        document.getElementById("temperature-level").innerHTML = data.temperatureLevel;
        document.getElementById("temperature-trend").innerHTML = data.temperatureTrend;
        document.getElementById("temperature-spike").innerHTML = data.temperatureSpike;

    }
    catch (error) {
        console.error('Error fetching data:', error);
    }
}