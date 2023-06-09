// pages/list/list.js
Page({
    /**
     * 页面的初始数据
     */
    data: {
        list:[{}],
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onShow(options){
        console.log(123)
        this.setData({list:[{}]})
        this.getList((result)=>{
            for(var i = 0;i < result.length;++i){
                // list
                this.setData({['list[' + i + '].userName']:result[i].name})
                this.setData({['list[' + i + '].userFire']:result[i].fire})
                this.setData({['list[' + i + '].userList']:i+1})
                this.setData({['list[' + i + '].userHead']:"https://liudi0303.cloud/head.jpg"})
            }
        });
    },
    onLoad(options) {
        this.getList((result)=>{
            for(var i = 0;i < result.length;++i){
                // list
                this.setData({['list[' + i + '].userName']:result[i].name})
                this.setData({['list[' + i + '].userFire']:result[i].fire})
                this.setData({['list[' + i + '].userList']:i+1})
                this.setData({['list[' + i + '].userHead']:"https://liudi0303.cloud/head?"+result[i].phone})
            }
        });
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

    getList(callback){
        wx.request({
            url: 'https://liudi0303.cloud/getList',
            header: {
                'content-type': 'application/json'
              },
            success:function(res){
                callback(res.data);
            }
          })
    },
})