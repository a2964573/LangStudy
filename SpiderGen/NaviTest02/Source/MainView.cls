import "Framework/afc/component/ANavigator.js";
import "Framework/afc/component/APanel.js";

/**
Constructor
Do not call Function in Constructor.
*/
class MainView()
{
	super();

	//TODO:edit here

}
extends AView;


function MainView*init(context, evtListener)
{
	super.init(context, evtListener);

	//TODO:edit here

	var viewCntr = this.view.loadContainer(null, "ViewCntr");

	theApp.navi = new ANavigator(null, viewCntr);
	this.regiPage();
	
	theApp.navi.goPage("Page0001");
};

function MainView*onInitDone()
{
	super.onInitDone();

	//TODO:edit here
	
};

function MainView*onActiveDone(isFirst)
{
	super.onActiveDone(isFirst);

	//TODO:edit here

};

function MainView*regiPage()
{
	theApp.navi.registerPage("Source/Pages/Page0001.lay", "Page0001");
	theApp.navi.registerPage("Source/Pages/Page0002.lay", "Page0002");
	theApp.navi.registerPage("Source/Pages/Page0003.lay", "Page0003");
};
