#ifndef TELEPIHTML_H
#define TELEPIHTML_H
const char purecss[] PROGMEM = R"=====(/*!
Pure v0.6.2
Copyright 2013 Yahoo!
Licensed under the BSD License.
https://github.com/yahoo/pure/blob/master/LICENSE.md
*/
/*!
normalize.css v^3.0 | MIT License | git.io/normalize
Copyright (c) Nicolas Gallagher and Jonathan Neal
*/
/*! normalize.css v3.0.3 | MIT License | github.com/necolas/normalize.css */.pure-button:focus,a:active,a:hover{outline:0}.pure-table,table{border-collapse:collapse;border-spacing:0}html{font-family:sans-serif;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}article,aside,details,figcaption,figure,footer,header,hgroup,main,menu,nav,section,summary{display:block}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}a{background-color:transparent}abbr[title]{border-bottom:1px dotted}b,optgroup,strong{font-weight:700}dfn{font-style:italic}h1{font-size:2em;margin:.67em 0}mark{background:#ff0;color:#000}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sup{top:-.5em}sub{bottom:-.25em}img{border:0}svg:not(:root){overflow:hidden}figure{margin:1em 40px}hr{box-sizing:content-box;height:0}pre,textarea{overflow:auto}code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}.pure-button,input{line-height:normal}button{overflow:visible}button,select{text-transform:none}button,html input[type=button],input[type=reset],input[type=submit]{-webkit-appearance:button;cursor:pointer}button[disabled],html input[disabled]{cursor:default}button::-moz-focus-inner,input::-moz-focus-inner{border:0;padding:0}input[type=checkbox],input[type=radio]{box-sizing:border-box;padding:0}input[type=number]::-webkit-inner-spin-button,input[type=number]::-webkit-outer-spin-button{height:auto}input[type=search]{-webkit-appearance:textfield;box-sizing:content-box}.pure-button,.pure-form input:not([type]),.pure-menu{box-sizing:border-box}input[type=search]::-webkit-search-cancel-button,input[type=search]::-webkit-search-decoration{-webkit-appearance:none}fieldset{border:1px solid silver;margin:0 2px;padding:.35em .625em .75em}legend,td,th{padding:0}legend{border:0}.hidden,[hidden]{display:none!important}.pure-img{max-width:100%;height:auto;display:block}.pure-g{letter-spacing:-.31em;text-rendering:optimizespeed;font-family:FreeSans,Arimo,"Droid Sans",Helvetica,Arial,sans-serif;display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-flex-flow:row wrap;-ms-flex-flow:row wrap;flex-flow:row wrap;-webkit-align-content:flex-start;-ms-flex-line-pack:start;align-content:flex-start}@media all and (-ms-high-contrast:none),(-ms-high-contrast:active){table .pure-g{display:block}}.opera-only :-o-prefocus,.pure-g{word-spacing:-.43em}.pure-u,.pure-u-1,.pure-u-1-1,.pure-u-1-12,.pure-u-1-2,.pure-u-1-24,.pure-u-1-3,.pure-u-1-4,.pure-u-1-5,.pure-u-1-6,.pure-u-1-8,.pure-u-10-24,.pure-u-11-12,.pure-u-11-24,.pure-u-12-24,.pure-u-13-24,.pure-u-14-24,.pure-u-15-24,.pure-u-16-24,.pure-u-17-24,.pure-u-18-24,.pure-u-19-24,.pure-u-2-24,.pure-u-2-3,.pure-u-2-5,.pure-u-20-24,.pure-u-21-24,.pure-u-22-24,.pure-u-23-24,.pure-u-24-24,.pure-u-3-24,.pure-u-3-4,.pure-u-3-5,.pure-u-3-8,.pure-u-4-24,.pure-u-4-5,.pure-u-5-12,.pure-u-5-24,.pure-u-5-5,.pure-u-5-6,.pure-u-5-8,.pure-u-6-24,.pure-u-7-12,.pure-u-7-24,.pure-u-7-8,.pure-u-8-24,.pure-u-9-24{letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto;display:inline-block;zoom:1}.pure-g [class*=pure-u]{font-family:sans-serif}.pure-u-1-24{width:4.1667%}.pure-u-1-12,.pure-u-2-24{width:8.3333%}.pure-u-1-8,.pure-u-3-24{width:12.5%}.pure-u-1-6,.pure-u-4-24{width:16.6667%}.pure-u-1-5{width:20%}.pure-u-5-24{width:20.8333%}.pure-u-1-4,.pure-u-6-24{width:25%}.pure-u-7-24{width:29.1667%}.pure-u-1-3,.pure-u-8-24{width:33.3333%}.pure-u-3-8,.pure-u-9-24{width:37.5%}.pure-u-2-5{width:40%}.pure-u-10-24,.pure-u-5-12{width:41.6667%}.pure-u-11-24{width:45.8333%}.pure-u-1-2,.pure-u-12-24{width:50%}.pure-u-13-24{width:54.1667%}.pure-u-14-24,.pure-u-7-12{width:58.3333%}.pure-u-3-5{width:60%}.pure-u-15-24,.pure-u-5-8{width:62.5%}.pure-u-16-24,.pure-u-2-3{width:66.6667%}.pure-u-17-24{width:70.8333%}.pure-u-18-24,.pure-u-3-4{width:75%}.pure-u-19-24{width:79.1667%}.pure-u-4-5{width:80%}.pure-u-20-24,.pure-u-5-6{width:83.3333%}.pure-u-21-24,.pure-u-7-8{width:87.5%}.pure-u-11-12,.pure-u-22-24{width:91.6667%}.pure-u-23-24{width:95.8333%}.pure-u-1,.pure-u-1-1,.pure-u-24-24,.pure-u-5-5{width:100%}.pure-button{display:inline-block;zoom:1;white-space:nowrap;vertical-align:middle;text-align:center;cursor:pointer;-webkit-user-drag:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}.pure-button::-moz-focus-inner{padding:0;border:0}.pure-button-group{letter-spacing:-.31em;text-rendering:optimizespeed}.opera-only :-o-prefocus,.pure-button-group{word-spacing:-.43em}.pure-button{font-family:inherit;font-size:100%;padding:.5em 1em;color:#444;color:rgba(0,0,0,.8);border:1px solid #999;border:transparent;background-color:#E6E6E6;text-decoration:none;border-radius:2px}.pure-button-hover,.pure-button:focus,.pure-button:hover{filter:alpha(opacity=90);background-image:-webkit-linear-gradient(transparent,rgba(0,0,0,.05) 40%,rgba(0,0,0,.1));background-image:linear-gradient(transparent,rgba(0,0,0,.05) 40%,rgba(0,0,0,.1))}.pure-button-active,.pure-button:active{box-shadow:0 0 0 1px rgba(0,0,0,.15) inset,0 0 6px rgba(0,0,0,.2) inset;border-color:#000\9}.pure-button-disabled,.pure-button-disabled:active,.pure-button-disabled:focus,.pure-button-disabled:hover,.pure-button[disabled]{border:none;background-image:none;filter:alpha(opacity=40);opacity:.4;cursor:not-allowed;box-shadow:none;pointer-events:none}.pure-button-hidden{display:none}.pure-button-primary,.pure-button-selected,a.pure-button-primary,a.pure-button-selected{background-color:#0078e7;color:#fff}.pure-button-group .pure-button{letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto;margin:0;border-radius:0;border-right:1px solid #111;border-right:1px solid rgba(0,0,0,.2)}.pure-button-group .pure-button:first-child{border-top-left-radius:2px;border-bottom-left-radius:2px}.pure-button-group .pure-button:last-child{border-top-right-radius:2px;border-bottom-right-radius:2px;border-right:none}.pure-form input[type=password],.pure-form input[type=email],.pure-form input[type=url],.pure-form input[type=date],.pure-form input[type=month],.pure-form input[type=time],.pure-form input[type=datetime],.pure-form input[type=datetime-local],.pure-form input[type=week],.pure-form input[type=tel],.pure-form input[type=color],.pure-form input[type=number],.pure-form input[type=search],.pure-form input[type=text],.pure-form select,.pure-form textarea{padding:.5em .6em;display:inline-block;border:1px solid #ccc;box-shadow:inset 0 1px 3px #ddd;border-radius:4px;vertical-align:middle;box-sizing:border-box}.pure-form input:not([type]){padding:.5em .6em;display:inline-block;border:1px solid #ccc;box-shadow:inset 0 1px 3px #ddd;border-radius:4px}.pure-form input[type=color]{padding:.2em .5em}.pure-form input:not([type]):focus,.pure-form input[type=password]:focus,.pure-form input[type=email]:focus,.pure-form input[type=url]:focus,.pure-form input[type=date]:focus,.pure-form input[type=month]:focus,.pure-form input[type=time]:focus,.pure-form input[type=datetime]:focus,.pure-form input[type=datetime-local]:focus,.pure-form input[type=week]:focus,.pure-form input[type=tel]:focus,.pure-form input[type=color]:focus,.pure-form input[type=number]:focus,.pure-form input[type=search]:focus,.pure-form input[type=text]:focus,.pure-form select:focus,.pure-form textarea:focus{outline:0;border-color:#129FEA}.pure-form input[type=file]:focus,.pure-form input[type=checkbox]:focus,.pure-form input[type=radio]:focus{outline:#129FEA auto 1px}.pure-form .pure-checkbox,.pure-form .pure-radio{margin:.5em 0;display:block}.pure-form input:not([type])[disabled],.pure-form input[type=password][disabled],.pure-form input[type=email][disabled],.pure-form input[type=url][disabled],.pure-form input[type=date][disabled],.pure-form input[type=month][disabled],.pure-form input[type=time][disabled],.pure-form input[type=datetime][disabled],.pure-form input[type=datetime-local][disabled],.pure-form input[type=week][disabled],.pure-form input[type=tel][disabled],.pure-form input[type=color][disabled],.pure-form input[type=number][disabled],.pure-form input[type=search][disabled],.pure-form input[type=text][disabled],.pure-form select[disabled],.pure-form textarea[disabled]{cursor:not-allowed;background-color:#eaeded;color:#cad2d3}.pure-form input[readonly],.pure-form select[readonly],.pure-form textarea[readonly]{background-color:#eee;color:#777;border-color:#ccc}.pure-form input:focus:invalid,.pure-form select:focus:invalid,.pure-form textarea:focus:invalid{color:#b94a48;border-color:#e9322d}.pure-form input[type=file]:focus:invalid:focus,.pure-form input[type=checkbox]:focus:invalid:focus,.pure-form input[type=radio]:focus:invalid:focus{outline-color:#e9322d}.pure-form select{height:2.25em;border:1px solid #ccc;background-color:#fff}.pure-form select[multiple]{height:auto}.pure-form label{margin:.5em 0 .2em}.pure-form fieldset{margin:0;padding:.35em 0 .75em;border:0}.pure-form legend{display:block;width:100%;padding:.3em 0;margin-bottom:.3em;color:#333;border-bottom:1px solid #e5e5e5}.pure-form-stacked input:not([type]),.pure-form-stacked input[type=password],.pure-form-stacked input[type=email],.pure-form-stacked input[type=url],.pure-form-stacked input[type=date],.pure-form-stacked input[type=month],.pure-form-stacked input[type=time],.pure-form-stacked input[type=datetime],.pure-form-stacked input[type=datetime-local],.pure-form-stacked input[type=week],.pure-form-stacked input[type=tel],.pure-form-stacked input[type=color],.pure-form-stacked input[type=file],.pure-form-stacked input[type=number],.pure-form-stacked input[type=search],.pure-form-stacked input[type=text],.pure-form-stacked label,.pure-form-stacked select,.pure-form-stacked textarea{display:block;margin:.25em 0}.pure-form-aligned .pure-help-inline,.pure-form-aligned input,.pure-form-aligned select,.pure-form-aligned textarea,.pure-form-message-inline{display:inline-block;vertical-align:middle}.pure-form-aligned textarea{vertical-align:top}.pure-form-aligned .pure-control-group{margin-bottom:.5em}.pure-form-aligned .pure-control-group label{text-align:right;display:inline-block;vertical-align:middle;width:10em;margin:0 1em 0 0}.pure-form-aligned .pure-controls{margin:1.5em 0 0 11em}.pure-form .pure-input-rounded,.pure-form input.pure-input-rounded{border-radius:2em;padding:.5em 1em}.pure-form .pure-group fieldset{margin-bottom:10px}.pure-form .pure-group input,.pure-form .pure-group textarea{display:block;padding:10px;margin:0 0 -1px;border-radius:0;position:relative;top:-1px}.pure-form .pure-group input:focus,.pure-form .pure-group textarea:focus{z-index:3}.pure-form .pure-group input:first-child,.pure-form .pure-group textarea:first-child{top:1px;border-radius:4px 4px 0 0;margin:0}.pure-form .pure-group input:first-child:last-child,.pure-form .pure-group textarea:first-child:last-child{top:1px;border-radius:4px;margin:0}.pure-form .pure-group input:last-child,.pure-form .pure-group textarea:last-child{top:-2px;border-radius:0 0 4px 4px;margin:0}.pure-form .pure-group button{margin:.35em 0}.pure-form .pure-input-1{width:100%}.pure-form .pure-input-3-4{width:75%}.pure-form .pure-input-2-3{width:66%}.pure-form .pure-input-1-2{width:50%}.pure-form .pure-input-1-3{width:33%}.pure-form .pure-input-1-4{width:25%}.pure-form .pure-help-inline,.pure-form-message-inline{display:inline-block;padding-left:.3em;color:#666;vertical-align:middle;font-size:.875em}.pure-form-message{display:block;color:#666;font-size:.875em}@media only screen and (max-width :480px){.pure-form button[type=submit]{margin:.7em 0 0}.pure-form input:not([type]),.pure-form input[type=password],.pure-form input[type=email],.pure-form input[type=url],.pure-form input[type=date],.pure-form input[type=month],.pure-form input[type=time],.pure-form input[type=datetime],.pure-form input[type=datetime-local],.pure-form input[type=week],.pure-form input[type=tel],.pure-form input[type=color],.pure-form input[type=number],.pure-form input[type=search],.pure-form input[type=text],.pure-form label{margin-bottom:.3em;display:block}.pure-group input:not([type]),.pure-group input[type=password],.pure-group input[type=email],.pure-group input[type=url],.pure-group input[type=date],.pure-group input[type=month],.pure-group input[type=time],.pure-group input[type=datetime],.pure-group input[type=datetime-local],.pure-group input[type=week],.pure-group input[type=tel],.pure-group input[type=color],.pure-group input[type=number],.pure-group input[type=search],.pure-group input[type=text]{margin-bottom:0}.pure-form-aligned .pure-control-group label{margin-bottom:.3em;text-align:left;display:block;width:100%}.pure-form-aligned .pure-controls{margin:1.5em 0 0}.pure-form .pure-help-inline,.pure-form-message,.pure-form-message-inline{display:block;font-size:.75em;padding:.2em 0 .8em}}.pure-menu-fixed{position:fixed;left:0;top:0;z-index:3}.pure-menu-item,.pure-menu-list{position:relative}.pure-menu-list{list-style:none;margin:0;padding:0}.pure-menu-item{padding:0;margin:0;height:100%}.pure-menu-heading,.pure-menu-link{display:block;text-decoration:none;white-space:nowrap}.pure-menu-horizontal{width:100%;white-space:nowrap}.pure-menu-horizontal .pure-menu-list{display:inline-block}.pure-menu-horizontal .pure-menu-heading,.pure-menu-horizontal .pure-menu-item,.pure-menu-horizontal .pure-menu-separator{display:inline-block;zoom:1;vertical-align:middle}.pure-menu-item .pure-menu-item{display:block}.pure-menu-children{display:none;position:absolute;left:100%;top:0;margin:0;padding:0;z-index:3}.pure-menu-horizontal .pure-menu-children{left:0;top:auto;width:inherit}.pure-menu-active>.pure-menu-children,.pure-menu-allow-hover:hover>.pure-menu-children{display:block;position:absolute}.pure-menu-has-children>.pure-menu-link:after{padding-left:.5em;content:"\25B8";font-size:small}.pure-menu-horizontal .pure-menu-has-children>.pure-menu-link:after{content:"\25BE"}.pure-menu-scrollable{overflow-y:scroll;overflow-x:hidden}.pure-menu-scrollable .pure-menu-list{display:block}.pure-menu-horizontal.pure-menu-scrollable .pure-menu-list{display:inline-block}.pure-menu-horizontal.pure-menu-scrollable{white-space:nowrap;overflow-y:hidden;overflow-x:auto;-ms-overflow-style:none;-webkit-overflow-scrolling:touch;padding:.5em 0}.pure-menu-horizontal.pure-menu-scrollable::-webkit-scrollbar{display:none}.pure-menu-horizontal .pure-menu-children .pure-menu-separator,.pure-menu-separator{background-color:#ccc;height:1px;margin:.3em 0}.pure-menu-horizontal .pure-menu-separator{width:1px;height:1.3em;margin:0 .3em}.pure-menu-horizontal .pure-menu-children .pure-menu-separator{display:block;width:auto}.pure-menu-heading{text-transform:uppercase;color:#565d64}.pure-menu-link{color:#777}.pure-menu-children{background-color:#fff}.pure-menu-disabled,.pure-menu-heading,.pure-menu-link{padding:.5em 1em}.pure-menu-disabled{opacity:.5}.pure-menu-disabled .pure-menu-link:hover{background-color:transparent}.pure-menu-active>.pure-menu-link,.pure-menu-link:focus,.pure-menu-link:hover{background-color:#eee}.pure-menu-selected .pure-menu-link,.pure-menu-selected .pure-menu-link:visited{color:#000}.pure-table{empty-cells:show;border:1px solid #cbcbcb}.pure-table caption{color:#000;font:italic 85%/1 arial,sans-serif;padding:1em 0;text-align:center}.pure-table td,.pure-table th{border-left:1px solid #cbcbcb;border-width:0 0 0 1px;font-size:inherit;margin:0;overflow:visible;padding:.5em 1em}.pure-table td:first-child,.pure-table th:first-child{border-left-width:0}.pure-table thead{background-color:#e0e0e0;color:#000;text-align:left;vertical-align:bottom}.pure-table td{background-color:transparent}.pure-table-odd td,.pure-table-striped tr:nth-child(2n-1) td{background-color:#f2f2f2}.pure-table-bordered td{border-bottom:1px solid #cbcbcb}.pure-table-bordered tbody>tr:last-child>td{border-bottom-width:0}.pure-table-horizontal td,.pure-table-horizontal th{border-width:0 0 1px;border-bottom:1px solid #cbcbcb}.pure-table-horizontal tbody>tr:last-child>td{border-bottom-width:0})=====";
const char jsuijs[] PROGMEM = R"=====((function (window, document) {

    var layout   = document.getElementById('layout'),
        menu     = document.getElementById('menu'),
        menuLink = document.getElementById('menuLink'),
        content  = document.getElementById('main'),

        mybutton = document.getElementById('mybutton');

    function toggleClass(element, className) {
        var classes = element.className.split(/\s+/),
            length = classes.length,
            i = 0;

        for(; i < length; i++) {
          if (classes[i] === className) {
            classes.splice(i, 1);
            break;
          }
        }
        // The className is not found
        if (length === classes.length) {
            classes.push(className);
        }

        element.className = classes.join(' ');
    }

    function toggleAll(e) {
        var active = 'active';

        e.preventDefault();
        toggleClass(layout, active);
        toggleClass(menu, active);
        toggleClass(menuLink, active);
    }

    menuLink.onclick = function (e) {
        toggleAll(e);
    };

    content.onclick = function(e) {
        if (menu.className.indexOf('active') !== -1) {
            toggleAll(e);
        }
    };

    mybutton.onclick = function (e) {
      var client = new XMLHttpRequest();
      client.open('GET', '/change');
      client.onreadystatechange = function() {
        // alert(client.responseText);
      }
      client.send();
    };

}(this, this.document));)=====";
const char sidemenucss[] PROGMEM = R"=====(body {
    color: #777;
}

.pure-img-responsive {
    max-width: 100%;
    height: auto;
}

/*
Add transition to containers so they can push in and out.
*/
#layout,
#menu,
.menu-link {
    -webkit-transition: all 0.2s ease-out;
    -moz-transition: all 0.2s ease-out;
    -ms-transition: all 0.2s ease-out;
    -o-transition: all 0.2s ease-out;
    transition: all 0.2s ease-out;
}

/*
This is the parent `<div>` that contains the menu and the content area.
*/
#layout {
    position: relative;
    left: 0;
    padding-left: 0;
}
    #layout.active #menu {
        left: 150px;
        width: 150px;
    }

    #layout.active .menu-link {
        left: 150px;
    }
/*
The content `<div>` is where all your content goes.
*/
.content {
    margin: 0 auto;
    padding: 0 2em;
    max-width: 800px;
    margin-bottom: 50px;
    line-height: 1.6em;
}

.header {
     margin: 0;
     color: #333;
     text-align: center;
     padding: 2.5em 2em 0;
     border-bottom: 1px solid #eee;
 }
    .header h1 {
        margin: 0.2em 0;
        font-size: 3em;
        font-weight: 300;
    }
     .header h2 {
        font-weight: 300;
        color: #ccc;
        padding: 0;
        margin-top: 0;
    }

.content-subhead {
    margin: 50px 0 20px 0;
    font-weight: 300;
    color: #888;
}



/*
The `#menu` `<div>` is the parent `<div>` that contains the `.pure-menu` that
appears on the left side of the page.
*/

#menu {
    margin-left: -150px; /* "#menu" width */
    width: 150px;
    position: fixed;
    top: 0;
    left: 0;
    bottom: 0;
    z-index: 1000; /* so the menu or its navicon stays above all content */
    background: #191818;
    overflow-y: auto;
    -webkit-overflow-scrolling: touch;
}
    /*
    All anchors inside the menu should be styled like this.
    */
    #menu a {
        color: #999;
        border: none;
        padding: 0.6em 0 0.6em 0.6em;
    }

    /*
    Remove all background/borders, since we are applying them to #menu.
    */
     #menu .pure-menu,
     #menu .pure-menu ul {
        border: none;
        background: transparent;
    }

    /*
    Add that light border to separate items into groups.
    */
    #menu .pure-menu ul,
    #menu .pure-menu .menu-item-divided {
        border-top: 1px solid #333;
    }
        /*
        Change color of the anchor links on hover/focus.
        */
        #menu .pure-menu li a:hover,
        #menu .pure-menu li a:focus {
            background: #333;
        }

    /*
    This styles the selected menu item `<li>`.
    */
    #menu .pure-menu-selected,
    #menu .pure-menu-heading {
        background: #1f8dd6;
    }
        /*
        This styles a link within a selected menu item `<li>`.
        */
        #menu .pure-menu-selected a {
            color: #fff;
        }

    /*
    This styles the menu heading.
    */
    #menu .pure-menu-heading {
        font-size: 110%;
        color: #fff;
        margin: 0;
    }

/* -- Dynamic Button For Responsive Menu -------------------------------------*/

/*
The button to open/close the Menu is custom-made and not part of Pure. Here's
how it works:
*/

/*
`.menu-link` represents the responsive menu toggle that shows/hides on
small screens.
*/
.menu-link {
    position: fixed;
    display: block; /* show this only on small screens */
    top: 0;
    left: 0; /* "#menu width" */
    background: #000;
    background: rgba(0,0,0,0.7);
    font-size: 10px; /* change this value to increase/decrease button size */
    z-index: 10;
    width: 2em;
    height: auto;
    padding: 2.1em 1.6em;
}

    .menu-link:hover,
    .menu-link:focus {
        background: #000;
    }

    .menu-link span {
        position: relative;
        display: block;
    }

    .menu-link span,
    .menu-link span:before,
    .menu-link span:after {
        background-color: #fff;
        width: 100%;
        height: 0.2em;
    }

        .menu-link span:before,
        .menu-link span:after {
            position: absolute;
            margin-top: -0.6em;
            content: " ";
        }

        .menu-link span:after {
            margin-top: 0.6em;
        }


/* -- Responsive Styles (Media Queries) ------------------------------------- */

/*
Hides the menu at `48em`, but modify this based on your app's needs.
*/
@media (min-width: 48em) {

    .header,
    .content {
        padding-left: 2em;
        padding-right: 2em;
    }

    #layout {
        padding-left: 150px; /* left col width "#menu" */
        left: 0;
    }
    #menu {
        left: 150px;
    }

    .menu-link {
        position: fixed;
        left: 150px;
        display: none;
    }

    #layout.active .menu-link {
        left: 150px;
    }
}

@media (max-width: 48em) {
    /* Only apply this when the window is small. Otherwise, the following
    case results in extra padding on the left:
        * Make the window small.
        * Tap the menu to trigger the active state.
        * Make the window large again.
    */
    #layout.active {
        position: relative;
        left: 150px;
    }
})=====";
const char buttoncss[] PROGMEM = R"=====(
          .myButton {
          	-moz-box-shadow: 3px 4px 0px 0px #1564ad;
          	-webkit-box-shadow: 3px 4px 0px 0px #1564ad;
          	box-shadow: 3px 4px 0px 0px #1564ad;
          	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #79bbff), color-stop(1, #378de5));
          	background:-moz-linear-gradient(top, #79bbff 5%, #378de5 100%);
          	background:-webkit-linear-gradient(top, #79bbff 5%, #378de5 100%);
          	background:-o-linear-gradient(top, #79bbff 5%, #378de5 100%);
          	background:-ms-linear-gradient(top, #79bbff 5%, #378de5 100%);
          	background:linear-gradient(to bottom, #79bbff 5%, #378de5 100%);
          	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#79bbff', endColorstr='#378de5',GradientType=0);
          	background-color:#79bbff;
          	-moz-border-radius:5px;
          	-webkit-border-radius:5px;
          	border-radius:5px;
          	border:1px solid #337bc4;
          	display:inline-block;
          	cursor:pointer;
          	color:#ffffff;
          	font-family:Arial;
          	font-size:17px;
          	font-weight:bold;
          	padding:12px 44px;
          	text-decoration:none;
          	text-shadow:0px 1px 0px #528ecc;
          }
          .myButton:hover {
          	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #378de5), color-stop(1, #79bbff));
          	background:-moz-linear-gradient(top, #378de5 5%, #79bbff 100%);
          	background:-webkit-linear-gradient(top, #378de5 5%, #79bbff 100%);
          	background:-o-linear-gradient(top, #378de5 5%, #79bbff 100%);
          	background:-ms-linear-gradient(top, #378de5 5%, #79bbff 100%);
          	background:linear-gradient(to bottom, #378de5 5%, #79bbff 100%);
          	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#378de5', endColorstr='#79bbff',GradientType=0);
          	background-color:#378de5;
          }
          .myButton:active {
          	position:relative;
          	top:1px;
          }          )=====";
const char sonoffsvgchar[] PROGMEM = R"=====(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   xmlns:dc="http://purl.org/dc/elements/1.1/"
   xmlns:cc="http://creativecommons.org/ns#"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:svg="http://www.w3.org/2000/svg"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   width="617.5"
   height="326"
   id="svg2"
   version="1.1"
   inkscape:version="0.48.5 r10040"
   sodipodi:docname="sonoff2.svg">
  <defs
     id="defs4" />
  <sodipodi:namedview
     id="base"
     pagecolor="#ffffff"
     bordercolor="#666666"
     borderopacity="1.0"
     inkscape:pageopacity="0.0"
     inkscape:pageshadow="2"
     inkscape:zoom="1"
     inkscape:cx="53.214286"
     inkscape:cy="-69.531081"
     inkscape:document-units="px"
     inkscape:current-layer="layer1"
     showgrid="false"
     inkscape:window-width="2560"
     inkscape:window-height="1374"
     inkscape:window-x="0"
     inkscape:window-y="27"
     inkscape:window-maximized="1"
     objecttolerance="20"
     fit-margin-top="0"
     fit-margin-left="0"
     fit-margin-right="0"
     fit-margin-bottom="0" />
  <metadata
     id="metadata7">
    <rdf:RDF>
      <cc:Work
         rdf:about="">
        <dc:format>image/svg+xml</dc:format>
        <dc:type
           rdf:resource="http://purl.org/dc/dcmitype/StillImage" />
        <dc:title></dc:title>
      </cc:Work>
    </rdf:RDF>
  </metadata>
  <g
     inkscape:label="Capa 1"
     inkscape:groupmode="layer"
     id="layer1"
     transform="translate(-56.5,-83.362183)">
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3000"
       width="615"
       height="324"
       x="58"
       y="84.362183"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2.02408385;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3770"
       width="69.64756"
       height="94"
       x="71"
       y="198.36218"
       rx="2.3878334"
       ry="2.7284927" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3772"
       width="95"
       height="168"
       x="217"
       y="113.36218"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3774"
       width="92"
       height="89"
       x="290"
       y="297.36218"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3776"
       width="71"
       height="95"
       x="585"
       y="160.36218"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3778"
       width="44"
       height="62"
       x="392"
       y="312.36218"
       rx="2.3313477"
       ry="2.7284927" />
    <path
       sodipodi:type="arc"
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3780"
       sodipodi:cx="207"
       sodipodi:cy="356.86218"
       sodipodi:rx="36"
       sodipodi:ry="35.5"
       d="m 243,356.86218 c 0,19.60611 -16.11775,35.5 -36,35.5 -19.88225,0 -36,-15.89389 -36,-35.5 0,-19.60611 16.11775,-35.5 36,-35.5 19.88225,0 36,15.89389 36,35.5 z"
       transform="matrix(1,0,0,1.0548193,2,-19.50901)" />
    <path
       sodipodi:type="arc"
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3780-3"
       sodipodi:cx="207"
       sodipodi:cy="356.86218"
       sodipodi:rx="36"
       sodipodi:ry="35.5"
       d="m 243,356.86218 c 0,19.60611 -16.11775,35.5 -36,35.5 -19.88225,0 -36,-15.89389 -36,-35.5 0,-19.60611 16.11775,-35.5 36,-35.5 19.88225,0 36,15.89389 36,35.5 z"
       transform="matrix(1,0,0,1.0548193,146,-122.06293)" />
    <rect
       style="fill:#000000;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3802"
       width="26"
       height="124"
       x="405"
       y="189.36218"
       rx="2.3313477"
       ry="2.7284927" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3804"
       sodipodi:cx="511"
       sodipodi:cy="342.36218"
       sodipodi:rx="13"
       sodipodi:ry="15"
       d="m 524,342.36218 c 0,8.28427 -5.8203,15 -13,15 -7.1797,0 -13,-6.71573 -13,-15 0,-8.28427 5.8203,-15 13,-15 7.1797,0 13,6.71573 13,15 z"
       transform="matrix(1.0635985,0,0,1,-31.672068,0)" />
    <rect
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2.07493567;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect3806"
       width="15.470426"
       height="15.584579"
       x="408.99091"
       y="290.77762"
       rx="2.2541838"
       ry="3.0373151" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3808"
       sodipodi:cx="417"
       sodipodi:cy="272.36218"
       sodipodi:rx="8"
       sodipodi:ry="7"
       d="m 425,272.36218 c 0,3.866 -3.58172,7 -8,7 -4.41828,0 -8,-3.134 -8,-7 0,-3.86599 3.58172,-7 8,-7 4.12125,0 7.56813,2.73954 7.96316,6.32903 L 417,272.36218 z"
       sodipodi:start="0"
       sodipodi:end="6.187185"
       transform="matrix(1,0,0,1.1143519,-0.27386762,-30.344674)" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3808-6"
       sodipodi:cx="417"
       sodipodi:cy="272.36218"
       sodipodi:rx="8"
       sodipodi:ry="7"
       d="m 425,272.36218 c 0,3.866 -3.58172,7 -8,7 -4.41828,0 -8,-3.134 -8,-7 0,-3.86599 3.58172,-7 8,-7 4.12125,0 7.56813,2.73954 7.96316,6.32903 L 417,272.36218 z"
       sodipodi:start="0"
       sodipodi:end="6.187185"
       transform="matrix(1,0,0,1.1143519,-0.27386762,-53.145133)" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3808-7"
       sodipodi:cx="417"
       sodipodi:cy="272.36218"
       sodipodi:rx="8"
       sodipodi:ry="7"
       d="m 425,272.36218 c 0,3.866 -3.58172,7 -8,7 -4.41828,0 -8,-3.134 -8,-7 0,-3.86599 3.58172,-7 8,-7 4.12125,0 7.56813,2.73954 7.96316,6.32903 L 417,272.36218 z"
       sodipodi:start="0"
       sodipodi:end="6.187185"
       transform="matrix(1,0,0,1.1143519,-0.27386762,-77.145133)" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path3808-5"
       sodipodi:cx="417"
       sodipodi:cy="272.36218"
       sodipodi:rx="8"
       sodipodi:ry="7"
       d="m 425,272.36218 c 0,3.866 -3.58172,7 -8,7 -4.41828,0 -8,-3.134 -8,-7 0,-3.86599 3.58172,-7 8,-7 4.12125,0 7.56813,2.73954 7.96316,6.32903 L 417,272.36218 z"
       sodipodi:start="0"
       sodipodi:end="6.187185"
       transform="matrix(1,0,0,1.1143519,-0.27386762,-101.14513)" />
    <text
       xml:space="preserve"
       style="font-size:40px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:FreeSerif;-inkscape-font-specification:FreeSerif"
       x="437"
       y="306.36218"
       id="text3842"
       sodipodi:linespacing="125%"><tspan
         sodipodi:role="line"
         id="tspan3844"
         x="437"
         y="306.36218"
         style="font-size:22px">1-Vcc</tspan></text>
    <text
       xml:space="preserve"
       style="font-size:40px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:FreeSerif;-inkscape-font-specification:FreeSerif"
       x="440.17084"
       y="234.67719"
       id="text3842-3"
       sodipodi:linespacing="125%"><tspan
         sodipodi:role="line"
         x="440.17084"
         y="234.67719"
         style="font-size:22px"
         id="tspan3867">4-GND</tspan></text>
    <text
       xml:space="preserve"
       style="font-size:40px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:FreeSerif;-inkscape-font-specification:FreeSerif"
       x="440.27173"
       y="282.6442"
       id="text3842-3-6"
       sodipodi:linespacing="125%"><tspan
         sodipodi:role="line"
         x="440.27173"
         y="282.6442"
         style="font-size:22px"
         id="tspan3867-2">2-RX - GPIO3</tspan></text>
    <text
       xml:space="preserve"
       style="font-size:40px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:FreeSerif;-inkscape-font-specification:FreeSerif"
       x="440.42599"
       y="258.79819"
       id="text3842-3-6-9"
       sodipodi:linespacing="125%"><tspan
         sodipodi:role="line"
         x="440.42599"
         y="258.79819"
         style="font-size:22px"
         id="tspan3867-2-1">3-TX - GPIO1</tspan></text>
    <text
       xml:space="preserve"
       style="font-size:40px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:FreeSerif;-inkscape-font-specification:FreeSerif"
       x="440.27173"
       y="209.6442"
       id="text3842-3-2"
       sodipodi:linespacing="125%"><tspan
         sodipodi:role="line"
         x="440.27173"
         y="209.6442"
         style="font-size:22px"
         id="tspan3867-7">5-GPIO14</tspan></text>
    <rect
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect4010"
       width="13"
       height="18"
       x="15"
       y="130"
       transform="translate(56.5,83.362183)"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect4012"
       width="13"
       height="19"
       x="15"
       y="176"
       transform="translate(56.5,83.362183)"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect4010-0"
       width="13"
       height="18"
       x="643"
       y="174.86218"
       rx="2.3313477"
       ry="2.7284927" />
    <rect
       style="fill:#003e00;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="rect4012-9"
       width="13"
       height="19"
       x="643"
       y="220.86218"
       rx="2.3313477"
       ry="2.7284927" />
    <path
       sodipodi:type="arc"
       style="fill:#003e00;fill-opacity:0;stroke:#000000;stroke-width:2;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none"
       id="path4037"
       sodipodi:cx="364.5"
       sodipodi:cy="270.5"
       sodipodi:rx="18.5"
       sodipodi:ry="19.5"
       d="m 383,270.5 a 18.5,19.5 0 1 1 -0.14365,-2.42531"
       transform="translate(50.5,73.362183)"
       sodipodi:start="0"
       sodipodi:end="6.1584873"
       sodipodi:open="true" />
  </g>
</svg>)=====";
const char indexhtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
    <link rel="stylesheet" type="text/css" href="css/button.css">
</head>
<body>
<div id="layout">
    <a href="#menu" id="menuLink" class="menu-link">
        <span></span>
    </a>
    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>
            <ul class="pure-menu-list">
              <li class="pure-menu-item"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-item"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-item"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-item"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-item"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>
    <div id="main">
       <div class="header">
         <div class="pure-g">
           <div class="pure-u-1-3">
             <a id="mybutton" class="myButton">ON/OFF</a>
           </div>
          <div class="pure-u-2-3">
            <h2>%eso  Uptime: %time</h2>
            <h2>Powered by TelePi.org</h2>
          </div>

       </div>
       <div class="content">
         <h2></h2>
         <img class="pure-img" src="sonoff.svg">
       </div>
    </div>
</div>

<script src="js/ui.js"></script>

</body>
</html>)=====";
const char wifisetuphtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
</head>
<body>
<div id="layout">
    <a href="#menu" id="menuLink" class="menu-link">
        <span></span>
    </a>

    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>

            <ul class="pure-menu-list">
              <li class="pure-menu-selected"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-item"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-item"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-item"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-item"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>

    <div id="main">
       <div class="header">
          <h2>%eso  Uptime: %time</h2>
          <h2>Powered by TelePi.org</h2>
       </div>
       <div class="content">
       <form class="pure-form pure-form-aligned">
         <fieldset>
            <legend>Wifi Configuration</legend>
          <div class="pure-control-group">
            <label for="hostname">Host Name</label>
            <input type="text" name="hostname" placeholder="hostame" value="%a1s" minlength="5" maxlength="15">
          </div>
          <div class="pure-control-group">
            <label for="wifimode">Wifi Mode</label>
            <select id="wifimode" name="wifimode">
              <option value="AP" %a2s>Access Point</option>
              <option value="CLI" %a3s>Client</option>
            </select>
          </div>
          <div class="pure-control-group">
            <label for="wifiSSID">SSID</label>
            <input type="text" name="wifiSSID" placeholder="SSID" value="%a5s" maxlength="15">
          </div>
          <div class="pure-control-group">
            <label for="wifipassword">Password</label>
            <input type="text" name="wifipassword" placeholder="password" value="%a6s" maxlength="30">
          </div>
        </fieldset>
        <fieldset>
            <legend>LAN Configuration</legend>
          <div class="pure-control-group">
            <label for="dhcp">DHCP</label>
            <select id="dhcp" name="dhcp">
              <option value="DHCP" %1s>DHCP Client</option>
              <option value="FIXIP" %2s>Fixed IP</option>
            </select>
          </div>
          <div class="pure-control-group">
            <label for="Wifi_IP">IP</label>
            <input type="text"  name="Wifi_IP" placeholder="192.168.0.5" value="%3s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$">
          </div>
          <div class="pure-control-group">
            <label for="Wifi_GW">Gateway</label>
            <input type="text"  name="Wifi_GW" placeholder="192.168.0.1" value="%4s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$">
          </div>
          <div class="pure-control-group">
            <label for="Wifi_MSK">Netmask</label>
            <input type="text"  name="Wifi_MSK" placeholder="255.255.255.0" value="%5s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$">
          </div>
          <div class="pure-control-group">
            <label for="Wifi_DNS">DNS</label>
            <input type="text"  name="Wifi_DNS" placeholder="255.255.255.0" value="%6s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$">
          </div>
        </fieldset>
        <fieldset>  <legend></legend>
          <input class="pure-button pure-button-primary" id="wifisetup" type="submit" name="save" value="Save">
          <input class="pure-button pure-button-primary" id="cancel" type="submit" name="cancel" value="Cancel">
        </fieldset>
      </form>
      </div>

    </div>
</div>

<script src="js/ui.js"></script>

</body>
</html>)=====";
const char workmodehtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
</head>
<body>

<div id="layout">
    <!-- Menu toggle -->
    <a href="#menu" id="menuLink" class="menu-link">
        <!-- Hamburger icon -->
        <span></span>
    </a>

    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>
            <ul class="pure-menu-list">
              <li class="pure-menu-item"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-selected"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-item"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-item"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-item"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>

    <div id="main">
      <div class="header">
         <h2>%eso  Uptime: %time</h2>
         <h2>Powered by TelePi.org</h2>
      </div>
      <div class="content">
      <form class="pure-form pure-form-aligned">
      <fieldset>
        <legend>Work Mode</legend>
      <div class="content" style="justify-content: center;text-align: center;">
      <table class="pure-table pure-table-bordered">
          <thead>
              <tr>
                  <th>I/O</th>
                  <th>Mode</th>
                  <th>Switch</th>
                  <th>Button</th>
              </tr>
          </thead>
          <tbody>
              <tr class="pure-table-odd">
                  <td>Relay(R)</td>
                  <td>OUT</td>
                  <td></td>
                  <td></td>
              </tr>
              <tr class="pure-table-odd">
                <td>Led</td>
                <td>
                  <select id="gpio13" name="gpio13">
                    <option value="Relay" %00a>Relay</option>
                    <option value="Pulse" %00b>Pulse</option>
                    <option value="NU" %00c>N/U</option>
                  </select>
                </td>
                <td></td>
                <td></td>
              </tr>

              <tr>
                <td>Button</td>
                <td>IN-Relay<br></td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio00sw" value="switch" %01></td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio00sw" value="push" %02></td>
              </tr>
              <tr>
                <td>GPIO14<br></td>
                <td>
                  <select id="gpio14" name="gpio14">
                    <option value="IN" %03>IN</option>
                    <option value="IN-R" %b3>IN-R</option>
                    <option value="OUT" %04>OUT</option>
                    <option value="NU" %05>N/U</option>
                  </select>
                </td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio14sw" value="switch" %06></td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio14sw" value="push" %07></td>
              </tr>
              <tr>
                <td>GPIO01<br></td>
                <td>
                  <select id="gpio01" name="gpio01">
                    <option value="IN" %08>IN</option>
                    <option value="IN-R" %b8>IN-R</option>
                    <option value="OUT" %09>OUT</option>
                    <option value="NU" %10>N/U</option>
                  </select>
                </td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio01sw" value="switch" %11></td>
                <td><input type="radio" style="transform: scale(1.5);" name="gpio01sw" value="push" %12></td>
              </tr>
              <tr>
                <td>GPIO03</td>
                <td>
                  <select id="gpio03" name="gpio03">
                    <option value="IN" %13>IN</option>
                    <option value="IN-R" %b13>IN-R</option>
                    <option value="OUT" %14>OUT</option>
                    <option value="NU" %15>N/U</option>
                  </select>
                </td>
                <td>
                    <input type="radio" style="transform: scale(1.5);" name="gpio03sw" value="switch" %16></td>
                  </label>
                <td>
                    <input type="radio" style="transform: scale(1.5);" name="gpio03sw" value="push" %17></td>
                  </label>
              </tr>

          </tbody>
      </table>
    </div>
    </fieldset>
    <fieldset>  <legend></legend>
      <input class="pure-button pure-button-primary" id="wifisetup" type="submit" name="save" value="Save">
      <input class="pure-button pure-button-primary" id="cancel" type="submit" name="cancel" value="Cancel">
    </fieldset>
    </form>
    </div>

    </div>
</div>

<script src="js/ui.js"></script>

</body>
</html>)=====";
const char linkwithhtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
</head>
<body>

<div id="layout">
    <!-- Menu toggle -->
    <a href="#menu" id="menuLink" class="menu-link">
        <!-- Hamburger icon -->
        <span></span>
    </a>

    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>
            <ul class="pure-menu-list">
              <li class="pure-menu-item"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-item"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-selected"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-item"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-item"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>

    <div id="main">
      <div class="header">
         <h2>%eso  Uptime: %time</h2>
         <h2>Powered by TelePi.org</h2>
      </div>
      <div class="content">
      <form class="pure-form pure-form-aligned">
      <fieldset>
        <legend>Link With another node</legend>
      <div class="content" style="justify-content: center;text-align: center;">
      <table class="pure-table pure-table-bordered">
          <thead>
              <tr>
                  <th>Local In</th>
                  <th>Mix</th>
                  <th>Abs</th>
                  <th>Remote IP</th>
                  <th>Remote Out</th>
              </tr>
          </thead>
          <tbody>
              <tr>
                <td>Button<br></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext1sw" value="switch" %1a></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext1sw" value="push" %1b></td>
                <td><input type="text"  name="ext1IP" placeholder="192.168.0.5" value="%1c" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"></td>
                <td>
                  <select id="ext1dest" name="ext1dest">
                    <option value="Disabled" %1d>Disabled</option>
                    <option value="Relay" %1e>Relay</option>
                    <option value="GPIO14" %1f>GPIO14</option>
                    <option value="GPIO01" %1g>GPIO01</option>
                    <option value="GPIO03" %1h>GPIO03</option>
                  </select>
                </td>
              </tr>
              <tr>
                <td>GPIO14<br></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext2sw" value="switch" %2a></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext2sw" value="push" %2b></td>
                <td><input type="text"  name="ext2IP" placeholder="192.168.0.5" value="%2c" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"></td>
                <td>
                  <select id="ext2dest" name="ext2dest">
                    <option value="Disabled" %2d>Disabled</option>
                    <option value="Relay" %2e>Relay</option>
                    <option value="GPIO14" %2f>GPIO14</option>
                    <option value="GPIO01" %2g>GPIO01</option>
                    <option value="GPIO03" %2h>GPIO03</option>
                  </select>
                </td>
              </tr>
              <tr>
                <td>GPIO01<br></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext3sw" value="switch" %3a></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext3sw" value="push" %3b></td>
                <td><input type="text"  name="ext3IP" placeholder="192.168.0.5" value="%3c" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"></td>
                <td>
                  <select id="ext3dest" name="ext3dest">
                    <option value="Disabled" %3d>Disabled</option>
                    <option value="Relay" %3e>Relay</option>
                    <option value="GPIO14" %3f>GPIO14</option>
                    <option value="GPIO01" %3g>GPIO01</option>
                    <option value="GPIO03" %3h>GPIO03</option>
                  </select>
                </td>
              </tr>
              <tr>
                <td>GPIO03<br></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext4sw" value="switch" %4a></td>
                <td><input type="radio" style="transform: scale(1.5);" name="ext4sw" value="push" %4b></td>
                <td><input type="text"  name="ext4IP" placeholder="192.168.0.5" value="%4c" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"></td>
                <td>
                  <select id="ext4dest" name="ext4dest">
                    <option value="Disabled" %4d>Disabled</option>
                    <option value="Relay" %4e>Relay</option>
                    <option value="GPIO14" %4f>GPIO14</option>
                    <option value="GPIO01" %4g>GPIO01</option>
                    <option value="GPIO03" %4h>GPIO03</option>
                  </select>
                </td>
              </tr>
          </tbody>
      </table>
    </div>
    </fieldset>
    <fieldset>  <legend></legend>
      <input class="pure-button pure-button-primary" id="wifisetup" type="submit" name="save" value="Save">
      <input class="pure-button pure-button-primary" id="cancel" type="submit" name="cancel" value="Cancel">
    </fieldset>
    </form>
    </div>

    </div>
</div>

<script src="js/ui.js"></script>

</body>
</html>)=====";
const char mqtthtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
</head>
<body>
<div id="layout">
    <a href="#menu" id="menuLink" class="menu-link">
        <span></span>
    </a>
    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>
            <ul class="pure-menu-list">
              <li class="pure-menu-item"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-item"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-item"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-selected"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-item"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>
    <div id="main">
       <div class="header">
          <h2>%eso  Uptime: %time</h2>
          <h2>Powered by TelePi.org</h2>
       </div>
       <div class="content">
       <form id="mqtthtml" class="pure-form pure-form-aligned" method="get">
         <fieldset>
            <legend>MQTT Configuration</legend>
          <div class="pure-control-group">
            <label for="hostname">Enable MQTT</label>
            <input type="hidden" name="MQTTenabled" value="off">
            <input type="checkbox"  style="transform: scale(1.5);" name="MQTTenabled" %0s>
          </div>
          <div class="pure-control-group">
            <label for="hostname">Topic</label>
            <input type="text" name="MQTTServerPath" placeholder="/TelePi/Sonoff" value="%1s" maxlength="39">
          </div>
          <div class="pure-control-group">
            <label for="hostname">Broker IP</label>
            <input type="text"  name="MQTT_IP" placeholder="192.168.0.5" value="%2s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$">
          </div>
          <div class="pure-control-group">
            <label for="hostname">Port</label>
            <input type="text"  name="MQTT_Port" placeholder="1883" value="%3s" required pattern="[0-9]{1,5}" maxlength="5">
          </div>
          <div class="pure-control-group">
            <label for="hostname">Password</label>
            <input type="text" name="MQTTpassword" placeholder="password" value="%4s" maxlength="30">
          </div>
        </fieldset>
        <fieldset>  <legend></legend>
          <button class="pure-button pure-button-primary" name="save" value="Save">Accept</button>
          <button class="pure-button pure-button-primary" onclick="window.location.href='index.html'" >Cancel</button>
        </fieldset>
      </form>
      </div>

    </div>
</div>




<script src="js/ui.js"></script>

</body>
</html>)=====";
const char updatehtml[] PROGMEM = R"=====(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="ESP8266 alternative firmware">
    <title>TelePi</title>
    <link rel="stylesheet" type="text/css" href="pure-release-0.6.2/pure-min.css">
    <link rel="stylesheet" type="text/css" href="css/layouts/side-menu.css">
</head>
<body>
<div id="layout">
    <a href="#menu" id="menuLink" class="menu-link">
        <span></span>
    </a>
    <div id="menu">
        <div class="pure-menu">
            <a class="pure-menu-heading" href="index.html">TelePi</a>
            <ul class="pure-menu-list">
              <li class="pure-menu-item"><a href="wifisetup.html" class="pure-menu-link">Wifi Setup</a></li>
              <li class="pure-menu-item"><a href="workmode.html" class="pure-menu-link">Work Mode</a></li>
              <li class="pure-menu-item"><a href="linkwith.html" class="pure-menu-link">Link With</a></li>
              <li class="pure-menu-item"><a href="mqtt.html" class="pure-menu-link">MQTT Update</a></li>
              <li class="pure-menu-selected"><a href="update.html" class="pure-menu-link">Firmware Update</a></li>
            </ul>
        </div>
    </div>
    <div id="main">
       <div class="header">
          <h2>%eso  Uptime: %time</h2>
          <h2>Powered by TelePi.org</h2>
       </div>
       <div class="content">
            <legend>Update Frimware</legend>
         <iframe src="update"  width="100%"></iframe>
      </div>
      <div class="content">
           <legend>Update Frimware</legend>
        <iframe src="config.txt"  width="100%"></iframe>
     </div>
    </div>
</div>

<script src="js/ui.js"></script>

</body>
</html>)=====";
#endif //TELEPIHTML_H
