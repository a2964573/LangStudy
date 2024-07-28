
/**
Constructor
Do not call Function in Constructor.
*/
class RootView()
{
	super();

	//TODO:edit here

}
extends AView;


function RootView*init(context, evtListener)
{
	super.init(context, evtListener);

	//TODO:edit here

	var thisObj = this;
	this.tabView.setTabOption({
		contentReload: true,
	});
	this.addTab(5, function(){
		thisObj.createBtn();
// 		thisObj.tabView.selectTabByIndex(0, { number: 0 });
	});
};

function RootView*onInitDone()
{
	super.onInitDone();

	//TODO:edit here

	this.onTabBtnClick(this.btnGrp.getChild(0));
};

function RootView*onActiveDone(isFirst)
{
	super.onActiveDone(isFirst);

	//TODO:edit here

};

function RootView*addTab(tabCnt, callback)
{
	var thisObj = this;
	
	for(var i = 0; i < tabCnt; i++){
		this.tabView.addTab(
			"tab"+i, 
			"Source/SubView/TabView.lay", 
			"tab"+i, 
			{ number: i },
			null,
			true
		);
	}
	
	if(this.tabView.getAllTabs().length == tabCnt){
		callback();
	}else{
		console.error("탭 뷰가 정상적으로 생성되지 않았습니다");
	}
	
};

function RootView*createBtn()
{
	var btnCnt = this.tabView.getAllTabs().length;
	
	var btnStyle = {
		"display": "block",
		"position": "relative",
		"width": "100%",
		"height": "100%",
		"background-color": "green",
		"outline": "1px solid #333",
		"font-size": "16px",
		"text-align": "center",
		"font-weight": "bold",
	};
	
	for(var i = 0; i < btnCnt; i++){
		var btn = new AButton();
		
		btn.init("AButton");
		btn.setOption({ isCheckBtn: true });
		btn.compId = "tab" + i;
		btn.setStyleObj(btnStyle);
		btn.saveBaseState();
		btn.addEventListener("click", this, "onTabBtnClick");
		
		this.btnGrp.addComponent(btn);
	}
};

function RootView*onTabBtnClick(comp){
	this.tabView.selectTabById(comp.compId, { number: comp.compId });
	
	this.btnGrp.getChildren().forEach(function(element, index){
		if(comp.compId == element.compId){
			element.setCheck(true);
			element.setStyle("background-color", "blue");
		}else{
			element.setCheck(false);
			element.setStyle("background-color", "green");
		}
	});
};

function RootView*onAButton1Click(comp, info, e)
{

	//TODO:edit here

};
