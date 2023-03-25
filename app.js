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
      serverIp:'101.42.35.137',
      port:8080,
  },
  //get image
  getImage:function(path){
      var app = getApp()
      console.log(app.data.serverIp + ':' + app.data.port)
    wx.request({
      url: 'http://' + app.data.serverIp + ':' + app.data.port,
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
