$.fn.extend({
    animateCss: function (animationName) {
        var animationEnd = 'webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend';

        $(this).addClass('animated ' + animationName).one(animationEnd, function() {
            $(this).removeClass('animated ' + animationName);
        }).one(animationEnd, function() {
            $(this).addClass('displaynone');
        });

    }
});

// $('h1').animateCss('pulse');

$('.scrollbanner').mouseover(function() {
  $('.scrollbanner').animateCss('rubberBand');
});

setTimeout(function(){
  randomAnimate();
}, 3000);

function randomAnimate () {
  var ranNum = Math.floor((Math.random() * 7) + 1);
    if (ranNum == 1) {
      $('.scrollbanner').animateCss('tada');
    } else if (ranNum == 2) {
      $('.scrollbanner').animateCss('swing');
    } else if (ranNum == 3) {
      $('.scrollbanner').animateCss('shake');
    } else if (ranNum == 4) {
      $('.scrollbanner').animateCss('pulse');
    } else if (ranNum == 5) {
      $('.scrollbanner').animateCss('bounce');
    } else if (ranNum == 6) {
      $('.scrollbanner').animateCss('jello');
    } else {}
 setTimeout(function(){
    randomAnimate();
  }, 3000);
}

function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

/* You DO need JavaScript to play and pause videos.
   However, you don't need jQuery */

document.querySelector('div.grid').addEventListener('mouseover',function(e){
  var evt = (e.target || this);
  if (evt.tagName.toLowerCase() === 'video'){
    !!(evt.paused) && evt.play();
  }
});

document.querySelector('div.grid').addEventListener('mouseout',function(e){
  var evt = (e.target || this);
  if (evt.tagName.toLowerCase() === 'video'){
    !(evt.paused) && evt.pause();
  }
});

var markers = [];
var geocoder = '';
var map = '';

var addMarker = function (location) {
  map.setCenter(location);

  removeMarker();

  var marker = new google.maps.Marker({
    map: map,
    position: location
  });

  markers.push(marker);
};
var removeMarker = function () {
  for (var a = 0, al = markers.length; a < al; a++) {
    markers[a].setMap(null);
  }

  markers = [];
};

var geocodeLatLng = function (geocoder, map, latlng) {
  geocoder.geocode({'location': latlng}, function(results, status) {
    if (status === 'OK' && results[0]) {
      addMarker(latlng);

      document.getElementById('latlng').value = latlng.lat + ',' + latlng.lng;

      document.getElementById('street_name').value = results[0].address_components[1].long_name;
      document.getElementById('street_number').value = results[0].address_components[0].long_name;
      document.getElementById('postal_code').value = results[0].address_components[5].long_name;
      document.getElementById('city').value = results[0].address_components[2].long_name;

    }
  });
};
var geocodeAddress = function (geocoder, map) {
  var addressTyped = document.getElementById('street_name').value + ' ' + document.getElementById('street_number').value + ', ' + document.getElementById('postal_code').value + ' ' + document.getElementById('city').value;

  geocoder.geocode({'address': addressTyped}, function(results, status) {
    if (status == 'OK') {
      var latlng = {
        lat: (results[0].geometry.viewport.f.b + results[0].geometry.viewport.f.f) / 2,
        lng: (results[0].geometry.viewport.b.b + results[0].geometry.viewport.b.f) / 2
      };

      addMarker(latlng);

      document.getElementById('latlng').value = latlng.lat + ',' + latlng.lng;
    }
  });
};

var initialize = function () {
  var mapCanvas = document.getElementById('map');
  var mapCenter = new google.maps.LatLng(50.4501, 30.5234);
  var mapOptions = {
    center: mapCenter,
    zoom: 16,
    mapTypeId: google.maps.MapTypeId.ROADMAP,

    scrollwheel: false,
    disableDefaultUI: true,

    // Custom Styling
    // https://snazzymaps.com/style/132/light-gray
    styles: [
      {
        "featureType":"water",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "color":"#d3d3d3"
          }
        ]
      },
      {
        "featureType":"transit",
        "stylers":[
          {
            "color":"#808080"
          },
          {
            "visibility":"off"
          }
        ]
      },
      {
        "featureType":"road.highway",
        "elementType":"geometry.stroke",
        "stylers":[
          {
            "visibility":"on"
          },
          {
            "color":"#b3b3b3"
          }
        ]
      },
      {
        "featureType":"road.highway",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "color":"#ffffff"
          }
        ]
      },
      {
        "featureType":"road.local",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "visibility":"on"
          },
          {
            "color":"#ffffff"
          },
          {
            "weight":1.8
          }
        ]
      },
      {
        "featureType":"road.local",
        "elementType":"geometry.stroke",
        "stylers":[
          {
            "color":"#d7d7d7"
          }
        ]
      },
      {
        "featureType":"poi",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "visibility":"on"
          },
          {
            "color":"#ebebeb"
          }
        ]
      },
      {
        "featureType":"administrative",
        "elementType":"geometry",
        "stylers":[
          {
            "color":"#a7a7a7"
          }
        ]
      },
      {
        "featureType":"road.arterial",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "color":"#ffffff"
          }
        ]
      },
      {
        "featureType":"road.arterial",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "color":"#ffffff"
          }
        ]
      },
      {
        "featureType":"landscape",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "visibility":"on"
          },
          {
            "color":"#efefef"
          }
        ]
      },
      {
        "featureType":"road",
        "elementType":"labels.text.fill",
        "stylers":[
          {
            "color":"#696969"
          }
        ]
      },
      {
        "featureType":"administrative",
        "elementType":"labels.text.fill",
        "stylers":[
          {
            "visibility":"on"
          },
          {
            "color":"#737373"
          }
        ]
      },
      {
        "featureType":"poi",
        "elementType":"labels.icon",
        "stylers":[
          {
            "visibility":"off"
          }
        ]
      },
      {
        "featureType":"poi",
        "elementType":"labels",
        "stylers":[
          {
            "visibility":"off"
          }
        ]
      },
      {
        "featureType":"road.arterial",
        "elementType":"geometry.stroke",
        "stylers":[
          {
            "color":"#d6d6d6"
          }
        ]
      },
      {
        "featureType":"road",
        "elementType":"labels.icon",
        "stylers":[
          {
            "visibility":"off"
          }
        ]
      },
      {

      },
      {
        "featureType":"poi",
        "elementType":"geometry.fill",
        "stylers":[
          {
            "color":"#dadada"
          }
        ]
      }
    ]
  };

  geocoder = new google.maps.Geocoder();
  map = new google.maps.Map(mapCanvas, mapOptions);

  if (navigator.geolocation) {
    var geolocationSuccess = function (position) {
      var latlng = {
        lat: position.coords.latitude,
        lng: position.coords.longitude
      };
      geocodeLatLng(geocoder, map, latlng);
    };
    var geolocationError = function (error) {
      alert('ERROR(' + error.code + '): ' + error.message);
    };
    var geolocationOptions = {
      enableHighAccuracy: true,
      timeout: 60000,
      maximumAge: Infinity
    };
    navigator.geolocation.getCurrentPosition(geolocationSuccess, geolocationError, geolocationOptions);
  }
};

google.maps.event.addDomListener(window, 'load', initialize);

document.querySelector('form.geo').addEventListener('submit', function (event) {
  event.preventDefault();
  geocodeAddress(geocoder, map);
});
