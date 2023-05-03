// index.js
// 获取应用实例
const app = getApp()
var interval;
Page({
    data: {
        isHiddenMsg: false,
        announcementText: "补习班刷榜活动火爆开始啦，朋友圈集赞拿好礼，还有免费课程赠送哦！",
        //滚动速度
        step: 1,
        //初始滚动距离
        distance: 0, 
        space: 30,
        // 时间间隔
        interval: 20, 
        swiperList:[{
            "imageUrl":"https://liudi0303.cloud/sliderWidget1.jpg"
        },
        {
            "imageUrl":"https://liudi0303.cloud/sliderWidget2.jpg"
        },
        {
            "imageUrl":"https://liudi0303.cloud/sliderWidget3.jpg"
        }],
        visitCount:20,
        indexImageMax:10,
        //活动结束时间
        overTime:0,
        overDay:0,
        overHour:0,
        overMinute:0,
        overSecond:0,

        swipCurrentIndex:0,
    },
    onShow(){
        this.getPhoneNunbers((result)=>{
            this.setData({"visitCount":result})
        });
    },
    onLoad(){
        this.topScroll();
        this.getPhoneNunbers((result)=>{
            this.setData({"visitCount":result})
        });

        this.getTimeOver((result)=>{
            this.setData({"overTime":result})
        });
        
        // this.setData({"visitCount":3})
        // this.formatTime((day,hour,minute,second)=>{
        //     this.setData({
        //         "overDay":day,
        //         "overHour":hour,
        //         "overMinute":minute,
        //         "overSecond":second,
        //     })
        // })

        //每秒刷新时间
        var that = this;
        setInterval(function() {
            that.formatTime((day,hour,minute,second)=>{
                that.setData({
                    "overDay":day,
                    "overHour":hour,
                    "overMinute":minute,
                    "overSecond":second,
                })
            })
         }, 1000);
    },

    /** 关闭顶部通知 */
      closeMsg(){
        this.setData({ isHiddenMsg: true});
        clearInterval(interval);
      },
      
     /** 获取滚动条基本信息 */
      topScroll(){
        var that = this;
        var query = wx.createSelectorQuery();
        //选择id
        query.select('#mjltest').boundingClientRect()
        query.exec(function (res) {
          var length = res[0].width;
          var windowWidth = wx.getSystemInfoSync().windowWidth; // 屏幕宽度
    
          that.setData({
            length: length,
            windowWidth: windowWidth,
            space: windowWidth
          });
          that.scrollling(); // 第一个字消失后立即从右边出现
        });
      },
      /** 向左滚动 */
      scrollling: function () {
        var that = this;
        var length = that.data.length; //滚动文字的宽度
        var windowWidth = that.data.windowWidth; //屏幕宽度
        let interval = setInterval(function () {
          var maxscrollwidth = length + that.data.space;
          var left = that.data.distance;
          if (left < maxscrollwidth) { //判断是否滚动到最大宽度
            that.setData({
              distance: left + that.data.step
            })
          } else {
            that.setData({
              distance: 0 // 直接重新滚动
            });
            clearInterval(interval);
            that.scrollling();
          }
        }, that.data.interval);
      },
      swipChanged:function(e){
          var cur = e.detail.current
          this.setData({
              swipCurrentIndex : cur
          })
      },
      getPhoneNumber (e) {
        var code = e.detail.code
        console.log(code)
        wx.request({
            url: 'https://liudi0303.cloud/getPhoneNumber?code='+code,
            header: {
                'content-type': 'application/json'
              },
            success:function(res){
                if(res.data == 'ok'){
                    app.data.submitResult = '报名成功!'
                }else{
                    app.data.submitResult = '您已报名!'
                }
                wx.navigateTo({
                    url: '/pages/phoneSubmit/phoneSubmit?data=1'
                  })
            }
          })
      },
      swipclick:function(e){
        if(this.data.swipCurrentIndex == 0){
            return
        }else if(this.data.swipCurrentIndex == 1){
            return
        }else if(this.data.swipCurrentIndex == 2){
            wx.navigateTo({
                url: '/pages/videoPage/videoPage'
              })
        }
    },
    //获取报名人数接口
        getPhoneNunbers:function(callback){
            wx.request({
                url: 'https://liudi0303.cloud/phoneNumbers',
                header: {
                    'content-type': 'application/json'
                  },
                success:function(res){
                    callback(res.data);
                }
              })
        },
        //获取活动结束时间
        getTimeOver:function(callback){
            wx.request({
                url: 'https://liudi0303.cloud/timeOver',
                header: {
                    'content-type': 'application/json'
                  },
                success:function(res){
                    callback(res.data);
                }
              })
        },
        //获取时间戳
        formatTime:function(callback) {//newDateTime
            var date = new Date()
            // var year = date.getFullYear();
            // var month = date.getMonth() + 1;
            // var day = date.getDate();
            // var hour = date.getHours();
            // var minute = date.getMinutes();
            // var second = date.getSeconds();
            //秒级时间戳
            var i = parseInt(date.getTime() / 1000);
            var t = this.data.overTime - i;
            var overDate = new Date(t);
            var allSecond = overDate.getTime();
            //天
            var overDay = parseInt(allSecond / (3600 * 24));
            //时
            var overHour = parseInt((allSecond - overDay * (3600 * 24)) / 3600);
            //分
            var overMinute = parseInt((allSecond - overDay * (3600 * 24) - overHour * 3600) / 60);
            //秒
            var overSecond = allSecond - overDay * (3600 * 24) - overHour * 3600 - overMinute * 60

            callback(overDay,overHour,overMinute,overSecond);
            // console.log(i)
            // console.log( year + "年" + month + "月" + day + "日" + hour + "时" + minute + "分" + second + "秒")
          }
    });
