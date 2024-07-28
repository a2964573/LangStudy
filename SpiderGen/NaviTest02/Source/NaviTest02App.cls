
/**
Constructor
Do not call Function in Constructor.
*/
class NaviTest02App()
{
	super();

	//TODO:edit here

	this.navi = null;
}
extends AApplication;


function NaviTest02App*onReady()
{
	super.onReady();

	this.setMainContainer(new APage('main'));
	this.mainContainer.open('Source/MainView.lay');

	//TODO:edit here
};

function NaviTest02App*unitTest(unitUrl)
{
	//TODO:edit here

	this.onReady();

	super.unitTest(unitUrl);
};
