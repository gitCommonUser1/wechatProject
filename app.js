// app.js
App({
  onLaunch() {
    // 展示本地存储能力
    const logs = wx.getStorageSync('logs') || []
    logs.unshift(Date.now())
    wx.setStorageSync('logs', logs)

    // 登录
    wx.login({
      success: res => {
        // 发送 res.code 到后台换取 openId, sessionKey, unionId
      }
    })
  },
  globalData: {
    userInfo: null
  },
  data:{
      serverIp:'liudi0303.cloud',
      port:443,
      submitResult:'报名成功!'
  },
   // 下拉刷新  
   onPullDownRefresh: function () {
    console.log('下拉')
    wx.startPullDownRefresh()
    setTimeout(()=>{
      wx.stopPullDownRefresh()
    },2000)
  },
  //get image
  getImage:function(path){
      var app = getApp()
      console.log(app.data.serverIp + ':' + app.data.port)
    wx.request({
      url: 'https://' + app.data.serverIp + ':' + app.data.port,
      success(res){
        // console.log(res)
        return res
      },
      fail(res){
        console.log(res)
      }
    })
},
})
