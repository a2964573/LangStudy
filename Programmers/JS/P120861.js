/** 캐릭터의 좌표
 * 머쓱이는 RPG게임을 하고 있습니다. 
 * 게임에는 up, down, left, right 방향키가 있으며 각 키를 누르면 위, 아래, 왼쪽, 오른쪽으로 한 칸씩 이동합니다. 
 * 예를 들어 [0,0]에서 up을 누른다면 캐릭터의 좌표는 [0, 1], 
 * down을 누른다면 [0, -1], left를 누른다면 [-1, 0], 
 * right를 누른다면 [1, 0]입니다. 
 * 머쓱이가 입력한 방향키의 배열 keyinput와 맵의 크기 board이 매개변수로 주어집니다. 
 * 캐릭터는 항상 [0,0]에서 시작할 때 키 입력이 모두 끝난 뒤에 캐릭터의 좌표 [x, y]를 return하도록 
 * solution 함수를 완성해주세요.
 */
function solution(keyEvent, board){
    board=[Math.floor(board[0]/2), Math.floor(board[1]/2)];
    var field={
        x: { min: -board[0], max: board[0] },
        y: { min: -board[1], max: board[1] },
    };

    var output=[0, 0];

    keyEvent.forEach((e)=>{
        var [x, y]=move(e, output);

        if(x<0) x=field.x.min<x?x:field.x.min;
        else    x=x<field.x.max?x:field.x.max;
        
        if(y<0) y=field.y.min<y?y:field.y.min;
        else    y=y<field.y.max?y:field.y.max;

        output=[x, y];
    });

    return output;
}

function move(keyEvent, location){
    var x=location[0], y=location[1];
    switch(keyEvent){
        case "left":    return [x-1, y];
        case "right":   return [x+1, y];
        case "up":      return [x, y+1];
        case "down":    return [x, y-1];
    }
}