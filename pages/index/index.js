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
            "imageUrl":"/images/commodity111.jpg"
        },
        {
            "imageUrl":"/images/commodity111.jpg"
        },
        {
            "imageUrl":"/images/commodity111.jpg"
        }],
        visitCount:20,
    },
    onLoad(){
        this.topScroll();
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

      swipclick:function(e){
        wx.navigateTo({
          url: '/pages/class/class'
        })
    },
    });

    