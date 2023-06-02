/** 배열의 유사도
 * 두 배열이 얼마나 유사한지 확인해보려고 합니다. 
 * 문자열 배열 s1과 s2가 주어질 때 같은 원소의 개수를 return하도록 solution 함수를 완성해주세요.
 */
function solution(s1, s2) {
    let count=0;
    s1.forEach((s1Element)=>{
        s2.forEach((s2Element)=>{
            if(s1Element===s2Element){
                count++;
            }
        })
    })
    return count;
}