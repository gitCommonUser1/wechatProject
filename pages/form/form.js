// pages/form/form.js
Page({

    /**
     * 页面的初始数据
     */
    data: {

    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad(options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady() {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow() {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide() {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload() {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh() {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom() {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage() {

    },
    buttonclick:function(e){


        // wx.switchTab({
        //     url: '/pages/index/index'
        // })
    },
    formSubmit:function(e){
        wx.request({
            url: 'http://101.42.35.137:8080/register?userName=' + e.detail.value.userName 
            + '&telephone=' + e.detail.value.telephone + '&sex=' + e.detail.value.sex,
            // header: {
            //     "Content-Type": "application/x-www-form-urlencoded"
            //   },
            // method:"POST",
            // data: JSON.stringify( { userName: "1234", telephone: "567" }),
        })
        console.log(e.detail.value.userName)
        
        // wx.switchTab({
        //     url: '/pages/index/index'
        // })
    },

    getPhoneNumber(e){
        let detail = e.detail;
        console.log(detail);
        if (detail.errMsg === "getPhoneNumber:ok") {
            console.log('用户同意授权');
            let code = detail.code; // 动态令牌
            console.log(code);
            wx.request({
                url: '你的接口，比如登录',
                data: {
                    code
                },
                success(res) {
                    console.log(res.data); // 后端返回解析出的手机号，或者直接返回登录成功的信息
                }
            })

        } else {
            console.log('用户拒绝授权');
        }
    }
})