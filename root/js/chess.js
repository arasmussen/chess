$(function() {
  var colors = {
    'b': 'black',
    'w': 'white'
  }

  var pieces = {
    'r': 'rook',
    'b': 'bishop',
    'n': 'knight',
    'q': 'queen',
    'k': 'king',
    'p': 'pawn'
  }

  function handleResponse(response) {
    var arr = response.split(' ');
    var cmd = arr[0];
    var square = arr[1];
    if (cmd == "remove") {
      remove(square);
    } else {
      var pieceNotation = arr[2];
      add(pieceNotation, square)
    }
  }

  function remove(square) {
    setHTMLAtSquare(square, '');
  }

  function add(pieceNotation, square) {
    var filename = getFileName(pieceNotation);
    setHTMLAtSquare(square, '<img src="' + filename + '" />');
  }

  function setHTMLAtSquare(square, html) {
    var col = square.charCodeAt(0) - 'a'.charCodeAt(0);
    var row = square.charAt(1);
    $($($('#game tr')[8 - row]).find('td')[col]).html(html);
  }

  function getFileName(pieceNotation) {
    var color = colors[pieceNotation.charAt(0)];
    var piece = pieces[pieceNotation.charAt(1)];
    var filename = '/img/' + color + '-' + piece + '.png';
    return filename;
  }
  handleResponse('remove e2');
  handleResponse('add e4 bk');
});
