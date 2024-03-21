/** 문자열 계산하기
 * my_string은 "3 + 5"처럼 문자열로 된 수식입니다. 
 * 문자열 my_string이 매개변수로 주어질 때, 
 * 수식을 계산한 값을 return 하는 solution 함수를 완성해주세요.
 */
function solution(input){
    var output;

    input=input.split(" ");

    for(var i=0; i<input.length; i++){
        if(/\d/.test(input[i])) continue;
        
        var prev=output==undefined?parseInt(input[i-1]):output;
        var next=parseInt(input[i+1]);

        switch(input[i]){
            case "+": output=prev+next; break;
            case "-": output=prev-next; break;
        }
    }

    return output;
}