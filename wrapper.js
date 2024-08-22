import Module from './quicked.js';
export function align() {
    var pattern = document.getElementById("pattern_in").value;
    var text = document.getElementById("text_in").value;

    Module().then(function(quicked) {
        // Size large enough for most cases ¯\_(ツ)_/¯
        const scorePtr = quicked._malloc(10);
        const cigarPtr = quicked._malloc((pattern.length+text.length)*2);

        var pat = quicked.stringToNewUTF8(pattern);
        var txt = quicked.stringToNewUTF8(text);

        var ret = quicked._quicked_aligner(pat, txt, scorePtr, cigarPtr);

        const score = quicked.getValue(scorePtr, 'i32');
        const cigar = quicked.UTF8ToString(cigarPtr);

        quicked._free(scorePtr);
        quicked._free(cigarPtr);

        if (ret == 0) {
            document.getElementById("score_text").innerHTML = score;
            document.getElementById("cigar_text").innerHTML = cigar;
        } else {
            document.getElementById("score_text").innerHTML = "Error";
            document.getElementById("cigar_text").innerHTML = "Error";
        }
    });
}