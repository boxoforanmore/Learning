(function() {
    if (window.myBookmarklet !== undefined) {
        myBookmarklet();
    }
    else {
        var el = document.createElement('script');
        el.src = 'https://7c9f1566.ngrok.io/static/js/bookmarklet.js?r=' + Math.floor(Math.random()*99999999999999999999);
        document.body.appendChild(el);
    }
})();