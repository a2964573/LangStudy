/** 외계어 사전
 * PROGRAMMERS-962 행성에 불시착한 우주비행사 머쓱이는 외계행성의 언어를 공부하려고 합니다. 
 * 알파벳이 담긴 배열 spell과 외계어 사전 dic이 매개변수로 주어집니다. 
 * spell에 담긴 알파벳을 한번씩만 모두 사용한 단어가 dic에 존재한다면 1, 존재하지 않는다면 2를 return하도록 
 * solution 함수를 완성해주세요.
 */
function solution(spell, dic) {
    const answer=dic.map((element)=>{
        let check=0;
        const temp=new Set(element);
        element=Array.from(temp);
        for(const e of temp){
            if(spell.find((alphabet)=>alphabet===e)){
                check++;
            }
        }
        return check===spell.length?1:2;
    })
    return answer.find((element)=>element===1)?1:2;
}